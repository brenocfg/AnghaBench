#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rdma_cm_id {int /*<<< orphan*/  device; struct isert_np* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct rdma_cm_event {TYPE_1__ param; } ;
struct isert_np {int /*<<< orphan*/  mutex; int /*<<< orphan*/  accepted; struct iscsi_np* np; } ;
struct isert_device {int dummy; } ;
struct isert_conn {int /*<<< orphan*/  node; struct isert_device* device; struct rdma_cm_id* cm_id; } ;
struct iscsi_np {int /*<<< orphan*/  np_thread_lock; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct isert_device*) ; 
 int PTR_ERR (struct isert_device*) ; 
 int isert_alloc_login_buf (struct isert_conn*,int /*<<< orphan*/ ) ; 
 int isert_conn_setup_qp (struct isert_conn*,struct rdma_cm_id*) ; 
 int /*<<< orphan*/  isert_dbg (char*,...) ; 
 struct isert_device* isert_device_get (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  isert_device_put (struct isert_device*) ; 
 int /*<<< orphan*/  isert_free_login_buf (struct isert_conn*) ; 
 int /*<<< orphan*/  isert_init_conn (struct isert_conn*) ; 
 int isert_login_post_recv (struct isert_conn*) ; 
 int isert_rdma_accept (struct isert_conn*) ; 
 int /*<<< orphan*/  isert_set_nego_params (struct isert_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct isert_conn*) ; 
 struct isert_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdma_reject (struct rdma_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isert_connect_request(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	struct isert_np *isert_np = cma_id->context;
	struct iscsi_np *np = isert_np->np;
	struct isert_conn *isert_conn;
	struct isert_device *device;
	int ret = 0;

	spin_lock_bh(&np->np_thread_lock);
	if (!np->enabled) {
		spin_unlock_bh(&np->np_thread_lock);
		isert_dbg("iscsi_np is not enabled, reject connect request\n");
		return rdma_reject(cma_id, NULL, 0);
	}
	spin_unlock_bh(&np->np_thread_lock);

	isert_dbg("cma_id: %p, portal: %p\n",
		 cma_id, cma_id->context);

	isert_conn = kzalloc(sizeof(struct isert_conn), GFP_KERNEL);
	if (!isert_conn)
		return -ENOMEM;

	isert_init_conn(isert_conn);
	isert_conn->cm_id = cma_id;

	ret = isert_alloc_login_buf(isert_conn, cma_id->device);
	if (ret)
		goto out;

	device = isert_device_get(cma_id);
	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		goto out_rsp_dma_map;
	}
	isert_conn->device = device;

	isert_set_nego_params(isert_conn, &event->param.conn);

	ret = isert_conn_setup_qp(isert_conn, cma_id);
	if (ret)
		goto out_conn_dev;

	ret = isert_login_post_recv(isert_conn);
	if (ret)
		goto out_conn_dev;

	ret = isert_rdma_accept(isert_conn);
	if (ret)
		goto out_conn_dev;

	mutex_lock(&isert_np->mutex);
	list_add_tail(&isert_conn->node, &isert_np->accepted);
	mutex_unlock(&isert_np->mutex);

	return 0;

out_conn_dev:
	isert_device_put(device);
out_rsp_dma_map:
	isert_free_login_buf(isert_conn);
out:
	kfree(isert_conn);
	rdma_reject(cma_id, NULL, 0);
	return ret;
}