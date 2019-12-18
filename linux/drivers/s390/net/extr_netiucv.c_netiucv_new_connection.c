#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct iucv_connection {void* rx_buff; void* tx_buff; int /*<<< orphan*/  list; int /*<<< orphan*/  fsm; int /*<<< orphan*/  userid; int /*<<< orphan*/  userdata; int /*<<< orphan*/  timer; int /*<<< orphan*/  max_buffsize; struct net_device* netdev; int /*<<< orphan*/  collect_lock; int /*<<< orphan*/  commit_queue; int /*<<< orphan*/  collect_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_FSM_LEN ; 
 int /*<<< orphan*/  CONN_STATE_INVALID ; 
 int /*<<< orphan*/  CONN_STATE_STOPPED ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NETIUCV_BUFSIZE_DEFAULT ; 
 int /*<<< orphan*/  NR_CONN_EVENTS ; 
 int /*<<< orphan*/  NR_CONN_STATES ; 
 void* alloc_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  conn_event_names ; 
 int /*<<< orphan*/  conn_fsm ; 
 int /*<<< orphan*/  conn_state_names ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_settimer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_fsm (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iucv_connection_list ; 
 int /*<<< orphan*/  iucv_connection_rwlock ; 
 int /*<<< orphan*/  kfree (struct iucv_connection*) ; 
 int /*<<< orphan*/  kfree_skb (void*) ; 
 struct iucv_connection* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iucv_connection *netiucv_new_connection(struct net_device *dev,
						      char *username,
						      char *userdata)
{
	struct iucv_connection *conn;

	conn = kzalloc(sizeof(*conn), GFP_KERNEL);
	if (!conn)
		goto out;
	skb_queue_head_init(&conn->collect_queue);
	skb_queue_head_init(&conn->commit_queue);
	spin_lock_init(&conn->collect_lock);
	conn->max_buffsize = NETIUCV_BUFSIZE_DEFAULT;
	conn->netdev = dev;

	conn->rx_buff = alloc_skb(conn->max_buffsize, GFP_KERNEL | GFP_DMA);
	if (!conn->rx_buff)
		goto out_conn;
	conn->tx_buff = alloc_skb(conn->max_buffsize, GFP_KERNEL | GFP_DMA);
	if (!conn->tx_buff)
		goto out_rx;
	conn->fsm = init_fsm("netiucvconn", conn_state_names,
			     conn_event_names, NR_CONN_STATES,
			     NR_CONN_EVENTS, conn_fsm, CONN_FSM_LEN,
			     GFP_KERNEL);
	if (!conn->fsm)
		goto out_tx;

	fsm_settimer(conn->fsm, &conn->timer);
	fsm_newstate(conn->fsm, CONN_STATE_INVALID);

	if (userdata)
		memcpy(conn->userdata, userdata, 17);
	if (username) {
		memcpy(conn->userid, username, 9);
		fsm_newstate(conn->fsm, CONN_STATE_STOPPED);
	}

	write_lock_bh(&iucv_connection_rwlock);
	list_add_tail(&conn->list, &iucv_connection_list);
	write_unlock_bh(&iucv_connection_rwlock);
	return conn;

out_tx:
	kfree_skb(conn->tx_buff);
out_rx:
	kfree_skb(conn->rx_buff);
out_conn:
	kfree(conn);
out:
	return NULL;
}