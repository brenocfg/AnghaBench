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
struct sockaddr {int dummy; } ;
struct ib_conn {int /*<<< orphan*/ * cma_id; int /*<<< orphan*/ * device; } ;
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  up_completion; int /*<<< orphan*/  name; struct ib_conn ib_conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  connlist_mutex; int /*<<< orphan*/  connlist; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ ISER_CONN_DOWN ; 
 scalar_t__ ISER_CONN_PENDING ; 
 scalar_t__ ISER_CONN_UP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 TYPE_1__ ig ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  iser_cma_handler ; 
 int /*<<< orphan*/  iser_conn_release (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  iser_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rdma_create_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_resolve_addr (int /*<<< orphan*/ *,struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,struct sockaddr*) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int iser_connect(struct iser_conn   *iser_conn,
		 struct sockaddr    *src_addr,
		 struct sockaddr    *dst_addr,
		 int                 non_blocking)
{
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	int err = 0;

	mutex_lock(&iser_conn->state_mutex);

	sprintf(iser_conn->name, "%pISp", dst_addr);

	iser_info("connecting to: %s\n", iser_conn->name);

	/* the device is known only --after-- address resolution */
	ib_conn->device = NULL;

	iser_conn->state = ISER_CONN_PENDING;

	ib_conn->cma_id = rdma_create_id(&init_net, iser_cma_handler,
					 (void *)iser_conn,
					 RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(ib_conn->cma_id)) {
		err = PTR_ERR(ib_conn->cma_id);
		iser_err("rdma_create_id failed: %d\n", err);
		goto id_failure;
	}

	err = rdma_resolve_addr(ib_conn->cma_id, src_addr, dst_addr, 1000);
	if (err) {
		iser_err("rdma_resolve_addr failed: %d\n", err);
		goto addr_failure;
	}

	if (!non_blocking) {
		wait_for_completion_interruptible(&iser_conn->up_completion);

		if (iser_conn->state != ISER_CONN_UP) {
			err =  -EIO;
			goto connect_failure;
		}
	}
	mutex_unlock(&iser_conn->state_mutex);

	mutex_lock(&ig.connlist_mutex);
	list_add(&iser_conn->conn_list, &ig.connlist);
	mutex_unlock(&ig.connlist_mutex);
	return 0;

id_failure:
	ib_conn->cma_id = NULL;
addr_failure:
	iser_conn->state = ISER_CONN_DOWN;
connect_failure:
	mutex_unlock(&iser_conn->state_mutex);
	iser_conn_release(iser_conn);
	return err;
}