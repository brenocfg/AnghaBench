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
struct ib_conn {int /*<<< orphan*/ * cma_id; } ;
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  ep; int /*<<< orphan*/  conn_list; struct ib_conn ib_conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  connlist_mutex; } ;

/* Variables and functions */
 scalar_t__ ISER_CONN_DOWN ; 
 TYPE_1__ ig ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_free_ib_conn_res (struct iser_conn*,int) ; 
 int /*<<< orphan*/  iser_warn (char*,struct iser_conn*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct iser_conn*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ *) ; 

void iser_conn_release(struct iser_conn *iser_conn)
{
	struct ib_conn *ib_conn = &iser_conn->ib_conn;

	mutex_lock(&ig.connlist_mutex);
	list_del(&iser_conn->conn_list);
	mutex_unlock(&ig.connlist_mutex);

	mutex_lock(&iser_conn->state_mutex);
	/* In case we endup here without ep_disconnect being invoked. */
	if (iser_conn->state != ISER_CONN_DOWN) {
		iser_warn("iser conn %p state %d, expected state down.\n",
			  iser_conn, iser_conn->state);
		iscsi_destroy_endpoint(iser_conn->ep);
		iser_conn->state = ISER_CONN_DOWN;
	}
	/*
	 * In case we never got to bind stage, we still need to
	 * release IB resources (which is safe to call more than once).
	 */
	iser_free_ib_conn_res(iser_conn, true);
	mutex_unlock(&iser_conn->state_mutex);

	if (ib_conn->cma_id != NULL) {
		rdma_destroy_id(ib_conn->cma_id);
		ib_conn->cma_id = NULL;
	}

	kfree(iser_conn);
}