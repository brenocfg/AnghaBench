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
struct qedr_qp {int /*<<< orphan*/  icid; } ;
struct qedr_dev {int /*<<< orphan*/  ibdev; } ;
struct qedr_create_qp_uresp {int /*<<< orphan*/  rq_icid; void* rq_db_offset; void* rq_db2_offset; } ;

/* Variables and functions */
 void* DB_ADDR_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_TCM_FLAGS ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_TCM_IWARP_RQ_PROD ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_TCM_ROCE_RQ_PROD ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qedr_copy_rq_uresp(struct qedr_dev *dev,
			       struct qedr_create_qp_uresp *uresp,
			       struct qedr_qp *qp)
{
	/* iWARP requires two doorbells per RQ. */
	if (rdma_protocol_iwarp(&dev->ibdev, 1)) {
		uresp->rq_db_offset =
		    DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_IWARP_RQ_PROD);
		uresp->rq_db2_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_FLAGS);
	} else {
		uresp->rq_db_offset =
		    DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_ROCE_RQ_PROD);
	}

	uresp->rq_icid = qp->icid;
}