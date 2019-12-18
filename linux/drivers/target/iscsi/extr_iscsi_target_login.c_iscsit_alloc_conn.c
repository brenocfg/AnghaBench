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
struct iscsi_np {int /*<<< orphan*/  np_transport; } ;
struct iscsi_conn_ops {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  conn_transport; struct iscsi_conn* conn_ops; int /*<<< orphan*/  conn_cpumask; int /*<<< orphan*/  nopin_timer; int /*<<< orphan*/  nopin_response_timer; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  response_queue_lock; int /*<<< orphan*/  nopin_timer_lock; int /*<<< orphan*/  immed_queue_lock; int /*<<< orphan*/  conn_usage_lock; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  rx_login_comp; int /*<<< orphan*/  tx_half_close_comp; int /*<<< orphan*/  rx_half_close_comp; int /*<<< orphan*/  conn_logout_comp; int /*<<< orphan*/  conn_waiting_on_uc_comp; int /*<<< orphan*/  conn_wait_rcfr_comp; int /*<<< orphan*/  conn_wait_comp; int /*<<< orphan*/  conn_post_wait_comp; int /*<<< orphan*/  response_queue_list; int /*<<< orphan*/  immed_queue_list; int /*<<< orphan*/  conn_cmd_list; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  queues_wq; int /*<<< orphan*/  conn_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TARG_CONN_STATE_FREE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ iscsit_conn_set_transport (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_handle_nopin_response_timeout ; 
 int /*<<< orphan*/  iscsit_handle_nopin_timeout ; 
 int /*<<< orphan*/  iscsit_put_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iscsi_conn*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iscsi_conn *iscsit_alloc_conn(struct iscsi_np *np)
{
	struct iscsi_conn *conn;

	conn = kzalloc(sizeof(struct iscsi_conn), GFP_KERNEL);
	if (!conn) {
		pr_err("Could not allocate memory for new connection\n");
		return NULL;
	}
	pr_debug("Moving to TARG_CONN_STATE_FREE.\n");
	conn->conn_state = TARG_CONN_STATE_FREE;

	init_waitqueue_head(&conn->queues_wq);
	INIT_LIST_HEAD(&conn->conn_list);
	INIT_LIST_HEAD(&conn->conn_cmd_list);
	INIT_LIST_HEAD(&conn->immed_queue_list);
	INIT_LIST_HEAD(&conn->response_queue_list);
	init_completion(&conn->conn_post_wait_comp);
	init_completion(&conn->conn_wait_comp);
	init_completion(&conn->conn_wait_rcfr_comp);
	init_completion(&conn->conn_waiting_on_uc_comp);
	init_completion(&conn->conn_logout_comp);
	init_completion(&conn->rx_half_close_comp);
	init_completion(&conn->tx_half_close_comp);
	init_completion(&conn->rx_login_comp);
	spin_lock_init(&conn->cmd_lock);
	spin_lock_init(&conn->conn_usage_lock);
	spin_lock_init(&conn->immed_queue_lock);
	spin_lock_init(&conn->nopin_timer_lock);
	spin_lock_init(&conn->response_queue_lock);
	spin_lock_init(&conn->state_lock);

	timer_setup(&conn->nopin_response_timer,
		    iscsit_handle_nopin_response_timeout, 0);
	timer_setup(&conn->nopin_timer, iscsit_handle_nopin_timeout, 0);

	if (iscsit_conn_set_transport(conn, np->np_transport) < 0)
		goto free_conn;

	conn->conn_ops = kzalloc(sizeof(struct iscsi_conn_ops), GFP_KERNEL);
	if (!conn->conn_ops) {
		pr_err("Unable to allocate memory for struct iscsi_conn_ops.\n");
		goto put_transport;
	}

	if (!zalloc_cpumask_var(&conn->conn_cpumask, GFP_KERNEL)) {
		pr_err("Unable to allocate conn->conn_cpumask\n");
		goto free_conn_ops;
	}

	return conn;

free_conn_ops:
	kfree(conn->conn_ops);
put_transport:
	iscsit_put_transport(conn->conn_transport);
free_conn:
	kfree(conn);
	return NULL;
}