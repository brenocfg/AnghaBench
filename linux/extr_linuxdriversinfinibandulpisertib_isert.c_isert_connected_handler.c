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
struct rdma_cm_id {struct isert_np* context; TYPE_1__* qp; } ;
struct isert_np {int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pending; int /*<<< orphan*/  node; int /*<<< orphan*/  kref; int /*<<< orphan*/  state; } ;
struct isert_conn {int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pending; int /*<<< orphan*/  node; int /*<<< orphan*/  kref; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct isert_np* qp_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_CONN_UP ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_np*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_connected_handler(struct rdma_cm_id *cma_id)
{
	struct isert_conn *isert_conn = cma_id->qp->qp_context;
	struct isert_np *isert_np = cma_id->context;

	isert_info("conn %p\n", isert_conn);

	mutex_lock(&isert_conn->mutex);
	isert_conn->state = ISER_CONN_UP;
	kref_get(&isert_conn->kref);
	mutex_unlock(&isert_conn->mutex);

	mutex_lock(&isert_np->mutex);
	list_move_tail(&isert_conn->node, &isert_np->pending);
	mutex_unlock(&isert_np->mutex);

	isert_info("np %p: Allow accept_np to continue\n", isert_np);
	up(&isert_np->sem);
}