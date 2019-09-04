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
typedef  scalar_t__ u64 ;
struct ehea_qp_init_attr {int rq_count; } ;
struct ehea_qp {int /*<<< orphan*/  hw_rqueue3; int /*<<< orphan*/  hw_rqueue2; int /*<<< orphan*/  hw_rqueue1; int /*<<< orphan*/  hw_squeue; int /*<<< orphan*/  fw_handle; TYPE_1__* adapter; struct ehea_qp_init_attr init_attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehea_h_disable_and_get_hea (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ehea_h_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_queue_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ehea_qp*) ; 

__attribute__((used)) static u64 ehea_destroy_qp_res(struct ehea_qp *qp, u64 force)
{
	u64 hret;
	struct ehea_qp_init_attr *qp_attr = &qp->init_attr;


	ehea_h_disable_and_get_hea(qp->adapter->handle, qp->fw_handle);
	hret = ehea_h_free_resource(qp->adapter->handle, qp->fw_handle, force);
	if (hret != H_SUCCESS)
		return hret;

	hw_queue_dtor(&qp->hw_squeue);
	hw_queue_dtor(&qp->hw_rqueue1);

	if (qp_attr->rq_count > 1)
		hw_queue_dtor(&qp->hw_rqueue2);
	if (qp_attr->rq_count > 2)
		hw_queue_dtor(&qp->hw_rqueue3);
	kfree(qp);

	return hret;
}