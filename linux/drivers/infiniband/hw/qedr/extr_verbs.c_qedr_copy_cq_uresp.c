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
typedef  int /*<<< orphan*/  uresp ;
struct qedr_dev {int dummy; } ;
struct qedr_create_cq_uresp {int /*<<< orphan*/  icid; int /*<<< orphan*/  db_offset; } ;
struct qedr_cq {int /*<<< orphan*/  icid; } ;
struct ib_udata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_ADDR_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_UCM_RDMA_CQ_CONS_32BIT ; 
 int /*<<< orphan*/  memset (struct qedr_create_cq_uresp*,int /*<<< orphan*/ ,int) ; 
 int qedr_ib_copy_to_udata (struct ib_udata*,struct qedr_create_cq_uresp*,int) ; 

__attribute__((used)) static int qedr_copy_cq_uresp(struct qedr_dev *dev,
			      struct qedr_cq *cq, struct ib_udata *udata)
{
	struct qedr_create_cq_uresp uresp;
	int rc;

	memset(&uresp, 0, sizeof(uresp));

	uresp.db_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_UCM_RDMA_CQ_CONS_32BIT);
	uresp.icid = cq->icid;

	rc = qedr_ib_copy_to_udata(udata, &uresp, sizeof(uresp));
	if (rc)
		DP_ERR(dev, "copy error cqid=0x%x.\n", cq->icid);

	return rc;
}