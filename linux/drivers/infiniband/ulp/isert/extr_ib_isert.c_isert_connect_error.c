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
struct rdma_cm_id {TYPE_1__* qp; } ;
struct isert_conn {int /*<<< orphan*/ * cm_id; int /*<<< orphan*/  node; int /*<<< orphan*/  qp; } ;
struct TYPE_2__ {struct isert_conn* qp_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_drain_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_put_conn (struct isert_conn*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isert_connect_error(struct rdma_cm_id *cma_id)
{
	struct isert_conn *isert_conn = cma_id->qp->qp_context;

	ib_drain_qp(isert_conn->qp);
	list_del_init(&isert_conn->node);
	isert_conn->cm_id = NULL;
	isert_put_conn(isert_conn);

	return -1;
}