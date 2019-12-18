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
struct qedr_qp {scalar_t__ icid; } ;
struct qedr_dev {int /*<<< orphan*/  ibdev; } ;
struct qedr_create_qp_uresp {scalar_t__ sq_icid; int /*<<< orphan*/  sq_db_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_ADDR_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qedr_copy_sq_uresp(struct qedr_dev *dev,
			       struct qedr_create_qp_uresp *uresp,
			       struct qedr_qp *qp)
{
	uresp->sq_db_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD);

	/* iWARP uses the same cid for rq and sq */
	if (rdma_protocol_iwarp(&dev->ibdev, 1))
		uresp->sq_icid = qp->icid;
	else
		uresp->sq_icid = qp->icid + 1;
}