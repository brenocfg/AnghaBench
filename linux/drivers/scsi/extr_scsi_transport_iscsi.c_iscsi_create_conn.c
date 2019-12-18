#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_transport {int dummy; } ;
struct iscsi_cls_session {int /*<<< orphan*/  dev; int /*<<< orphan*/  sid; struct iscsi_transport* transport; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct iscsi_cls_conn {int /*<<< orphan*/  conn_list; TYPE_1__ dev; int /*<<< orphan*/  cid; struct iscsi_transport* transport; int /*<<< orphan*/  ep_mutex; struct iscsi_cls_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISCSI_DBG_TRANS_CONN (struct iscsi_cls_conn*,char*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  connlist ; 
 int /*<<< orphan*/  connlock ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_cls_session_printk (int /*<<< orphan*/ ,struct iscsi_cls_session*,char*) ; 
 int /*<<< orphan*/  iscsi_conn_release ; 
 int /*<<< orphan*/  kfree (struct iscsi_cls_conn*) ; 
 struct iscsi_cls_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transport_register_device (TYPE_1__*) ; 

struct iscsi_cls_conn *
iscsi_create_conn(struct iscsi_cls_session *session, int dd_size, uint32_t cid)
{
	struct iscsi_transport *transport = session->transport;
	struct iscsi_cls_conn *conn;
	unsigned long flags;
	int err;

	conn = kzalloc(sizeof(*conn) + dd_size, GFP_KERNEL);
	if (!conn)
		return NULL;
	if (dd_size)
		conn->dd_data = &conn[1];

	mutex_init(&conn->ep_mutex);
	INIT_LIST_HEAD(&conn->conn_list);
	conn->transport = transport;
	conn->cid = cid;

	/* this is released in the dev's release function */
	if (!get_device(&session->dev))
		goto free_conn;

	dev_set_name(&conn->dev, "connection%d:%u", session->sid, cid);
	conn->dev.parent = &session->dev;
	conn->dev.release = iscsi_conn_release;
	err = device_register(&conn->dev);
	if (err) {
		iscsi_cls_session_printk(KERN_ERR, session, "could not "
					 "register connection's dev\n");
		goto release_parent_ref;
	}
	transport_register_device(&conn->dev);

	spin_lock_irqsave(&connlock, flags);
	list_add(&conn->conn_list, &connlist);
	spin_unlock_irqrestore(&connlock, flags);

	ISCSI_DBG_TRANS_CONN(conn, "Completed conn creation\n");
	return conn;

release_parent_ref:
	put_device(&session->dev);
free_conn:
	kfree(conn);
	return NULL;
}