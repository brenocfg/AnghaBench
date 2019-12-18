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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocrdma_qp {scalar_t__ ird_q_va; struct ocrdma_pd* pd; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct ocrdma_pd {TYPE_1__ ibpd; } ;
struct ocrdma_hdr_wqe {int cw; } ;
struct TYPE_6__ {int ird_page_size; int num_ird_pages; scalar_t__ ird; int rqe_size; } ;
struct TYPE_5__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_3__ attr; TYPE_2__ nic_info; } ;
struct ocrdma_create_qp_req {int /*<<< orphan*/ * ird_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OCRDMA_TYPE_LKEY ; 
 int OCRDMA_WQE_NXT_WQE_SIZE_SHIFT ; 
 int OCRDMA_WQE_SIZE_SHIFT ; 
 int OCRDMA_WQE_TYPE_SHIFT ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_build_q_pages (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocrdma_set_create_qp_ird_cmd(struct ocrdma_create_qp_req *cmd,
					struct ocrdma_qp *qp)
{
	struct ocrdma_pd *pd = qp->pd;
	struct ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);
	struct pci_dev *pdev = dev->nic_info.pdev;
	dma_addr_t pa = 0;
	int ird_page_size = dev->attr.ird_page_size;
	int ird_q_len = dev->attr.num_ird_pages * ird_page_size;
	struct ocrdma_hdr_wqe *rqe;
	int i  = 0;

	if (dev->attr.ird == 0)
		return 0;

	qp->ird_q_va = dma_alloc_coherent(&pdev->dev, ird_q_len, &pa,
					  GFP_KERNEL);
	if (!qp->ird_q_va)
		return -ENOMEM;
	ocrdma_build_q_pages(&cmd->ird_addr[0], dev->attr.num_ird_pages,
			     pa, ird_page_size);
	for (; i < ird_q_len / dev->attr.rqe_size; i++) {
		rqe = (struct ocrdma_hdr_wqe *)(qp->ird_q_va +
			(i * dev->attr.rqe_size));
		rqe->cw = 0;
		rqe->cw |= 2;
		rqe->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);
		rqe->cw |= (8 << OCRDMA_WQE_SIZE_SHIFT);
		rqe->cw |= (8 << OCRDMA_WQE_NXT_WQE_SIZE_SHIFT);
	}
	return 0;
}