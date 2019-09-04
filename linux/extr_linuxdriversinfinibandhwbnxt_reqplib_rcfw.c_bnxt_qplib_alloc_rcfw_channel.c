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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int max_elements; } ;
struct bnxt_qplib_rcfw {int qp_tbl_size; void* qp_tbl; void* crsqe_tbl; TYPE_1__ cmdq; struct pci_dev* pdev; TYPE_1__ creq; } ;
struct bnxt_qplib_qp_node {int dummy; } ;

/* Variables and functions */
 int BNXT_QPLIB_CMDQE_MAX_CNT ; 
 int /*<<< orphan*/  BNXT_QPLIB_CMDQE_UNITS ; 
 int BNXT_QPLIB_CREQE_MAX_CNT ; 
 int /*<<< orphan*/  BNXT_QPLIB_CREQE_UNITS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWQ_TYPE_CTX ; 
 int /*<<< orphan*/  HWQ_TYPE_L2_CMPL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ bnxt_qplib_alloc_init_hwq (struct pci_dev*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_free_rcfw_channel (struct bnxt_qplib_rcfw*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 

int bnxt_qplib_alloc_rcfw_channel(struct pci_dev *pdev,
				  struct bnxt_qplib_rcfw *rcfw,
				  int qp_tbl_sz)
{
	rcfw->pdev = pdev;
	rcfw->creq.max_elements = BNXT_QPLIB_CREQE_MAX_CNT;
	if (bnxt_qplib_alloc_init_hwq(rcfw->pdev, &rcfw->creq, NULL, 0,
				      &rcfw->creq.max_elements,
				      BNXT_QPLIB_CREQE_UNITS, 0, PAGE_SIZE,
				      HWQ_TYPE_L2_CMPL)) {
		dev_err(&rcfw->pdev->dev,
			"QPLIB: HW channel CREQ allocation failed");
		goto fail;
	}
	rcfw->cmdq.max_elements = BNXT_QPLIB_CMDQE_MAX_CNT;
	if (bnxt_qplib_alloc_init_hwq(rcfw->pdev, &rcfw->cmdq, NULL, 0,
				      &rcfw->cmdq.max_elements,
				      BNXT_QPLIB_CMDQE_UNITS, 0, PAGE_SIZE,
				      HWQ_TYPE_CTX)) {
		dev_err(&rcfw->pdev->dev,
			"QPLIB: HW channel CMDQ allocation failed");
		goto fail;
	}

	rcfw->crsqe_tbl = kcalloc(rcfw->cmdq.max_elements,
				  sizeof(*rcfw->crsqe_tbl), GFP_KERNEL);
	if (!rcfw->crsqe_tbl)
		goto fail;

	rcfw->qp_tbl_size = qp_tbl_sz;
	rcfw->qp_tbl = kcalloc(qp_tbl_sz, sizeof(struct bnxt_qplib_qp_node),
			       GFP_KERNEL);
	if (!rcfw->qp_tbl)
		goto fail;

	return 0;

fail:
	bnxt_qplib_free_rcfw_channel(rcfw);
	return -ENOMEM;
}