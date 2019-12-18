#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_10__ {TYPE_2__* sge; } ;
struct TYPE_11__ {TYPE_3__ nonemb_req; } ;
struct TYPE_8__ {int pyld_len; int spcl_sge_cnt_emb; } ;
struct ocrdma_mqe {TYPE_4__ u; TYPE_1__ hdr; } ;
struct ocrdma_mbx_hdr {int dummy; } ;
struct mgmt_hba_attribs {int ptpnum_maxdoms_hbast_cv; int /*<<< orphan*/  controller_model_number; } ;
struct TYPE_12__ {struct mgmt_hba_attribs hba_attribs; } ;
struct ocrdma_get_ctrl_attribs_rsp {TYPE_5__ ctrl_attribs; } ;
struct ocrdma_dma_mem {int size; int pa; scalar_t__ va; } ;
struct TYPE_14__ {TYPE_6__* pdev; } ;
struct ocrdma_dev {int hba_port_num; TYPE_7__ nic_info; int /*<<< orphan*/  model_number; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int len; void* pa_hi; void* pa_lo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OCRDMA_CMD_GET_CTRL_ATTRIBUTES ; 
 int OCRDMA_HBA_ATTRB_PTNUM_MASK ; 
 int OCRDMA_HBA_ATTRB_PTNUM_SHIFT ; 
 int OCRDMA_MQE_HDR_SGE_CNT_MASK ; 
 int OCRDMA_MQE_HDR_SGE_CNT_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_SUBSYS_COMMON ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_mqe*) ; 
 struct ocrdma_mqe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_init_mch (struct ocrdma_mbx_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ocrdma_nonemb_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ upper_32_bits (int) ; 

__attribute__((used)) static int ocrdma_mbx_get_ctrl_attribs(struct ocrdma_dev *dev)
{
	int status = -ENOMEM;
	struct ocrdma_dma_mem dma;
	struct ocrdma_mqe *mqe;
	struct ocrdma_get_ctrl_attribs_rsp *ctrl_attr_rsp;
	struct mgmt_hba_attribs *hba_attribs;

	mqe = kzalloc(sizeof(struct ocrdma_mqe), GFP_KERNEL);
	if (!mqe)
		return status;

	dma.size = sizeof(struct ocrdma_get_ctrl_attribs_rsp);
	dma.va	 = dma_alloc_coherent(&dev->nic_info.pdev->dev,
					dma.size, &dma.pa, GFP_KERNEL);
	if (!dma.va)
		goto free_mqe;

	mqe->hdr.pyld_len = dma.size;
	mqe->hdr.spcl_sge_cnt_emb |=
			(1 << OCRDMA_MQE_HDR_SGE_CNT_SHIFT) &
			OCRDMA_MQE_HDR_SGE_CNT_MASK;
	mqe->u.nonemb_req.sge[0].pa_lo = (u32) (dma.pa & 0xffffffff);
	mqe->u.nonemb_req.sge[0].pa_hi = (u32) upper_32_bits(dma.pa);
	mqe->u.nonemb_req.sge[0].len = dma.size;

	ocrdma_init_mch((struct ocrdma_mbx_hdr *)dma.va,
			OCRDMA_CMD_GET_CTRL_ATTRIBUTES,
			OCRDMA_SUBSYS_COMMON,
			dma.size);

	status = ocrdma_nonemb_mbx_cmd(dev, mqe, dma.va);
	if (!status) {
		ctrl_attr_rsp = (struct ocrdma_get_ctrl_attribs_rsp *)dma.va;
		hba_attribs = &ctrl_attr_rsp->ctrl_attribs.hba_attribs;

		dev->hba_port_num = (hba_attribs->ptpnum_maxdoms_hbast_cv &
					OCRDMA_HBA_ATTRB_PTNUM_MASK)
					>> OCRDMA_HBA_ATTRB_PTNUM_SHIFT;
		strlcpy(dev->model_number,
			hba_attribs->controller_model_number,
			sizeof(dev->model_number));
	}
	dma_free_coherent(&dev->nic_info.pdev->dev, dma.size, dma.va, dma.pa);
free_mqe:
	kfree(mqe);
	return status;
}