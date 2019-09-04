#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct t4_cqe {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_6__ {TYPE_2__ lldi; } ;
struct c4iw_dev {TYPE_3__ rdev; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CQE_OPCODE (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_QPID (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_STATUS (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_TYPE (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_WRID_HI (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_WRID_LOW (struct t4_cqe*) ; 
 int /*<<< orphan*/  CQE_WRID_STAG (struct t4_cqe*) ; 
 scalar_t__ FW_RI_RDMA_WRITE ; 
 scalar_t__ FW_RI_READ_RESP ; 
 scalar_t__ RQ_TYPE (struct t4_cqe*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_tpte (struct c4iw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_err_cqe(struct c4iw_dev *dev, struct t4_cqe *err_cqe)
{
	__be64 *p = (void *)err_cqe;

	dev_err(&dev->rdev.lldi.pdev->dev,
		"AE qpid %d opcode %d status 0x%x "
		"type %d len 0x%x wrid.hi 0x%x wrid.lo 0x%x\n",
		CQE_QPID(err_cqe), CQE_OPCODE(err_cqe),
		CQE_STATUS(err_cqe), CQE_TYPE(err_cqe), ntohl(err_cqe->len),
		CQE_WRID_HI(err_cqe), CQE_WRID_LOW(err_cqe));

	pr_debug("%016llx %016llx %016llx %016llx - %016llx %016llx %016llx %016llx\n",
		 be64_to_cpu(p[0]), be64_to_cpu(p[1]), be64_to_cpu(p[2]),
		 be64_to_cpu(p[3]), be64_to_cpu(p[4]), be64_to_cpu(p[5]),
		 be64_to_cpu(p[6]), be64_to_cpu(p[7]));

	/*
	 * Ingress WRITE and READ_RESP errors provide
	 * the offending stag, so parse and log it.
	 */
	if (RQ_TYPE(err_cqe) && (CQE_OPCODE(err_cqe) == FW_RI_RDMA_WRITE ||
				 CQE_OPCODE(err_cqe) == FW_RI_READ_RESP))
		print_tpte(dev, CQE_WRID_STAG(err_cqe));
}