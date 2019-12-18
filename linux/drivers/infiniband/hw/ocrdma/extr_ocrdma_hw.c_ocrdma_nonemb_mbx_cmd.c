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
struct TYPE_2__ {int spcl_sge_cnt_emb; } ;
struct ocrdma_mqe {TYPE_1__ hdr; } ;
struct ocrdma_mbx_rsp {int status; int subsys_op; } ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int OCRDMA_MBX_RSP_OPCODE_MASK ; 
 int OCRDMA_MBX_RSP_OPCODE_SHIFT ; 
 int OCRDMA_MBX_RSP_STATUS_MASK ; 
 int OCRDMA_MBX_RSP_SUBSYS_MASK ; 
 int OCRDMA_MBX_RSP_SUBSYS_SHIFT ; 
 int OCRDMA_MQE_HDR_EMB_MASK ; 
 int OCRDMA_MQE_HDR_EMB_SHIFT ; 
 int ocrdma_get_mbx_errno (int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int ocrdma_nonemb_mbx_cmd(struct ocrdma_dev *dev, struct ocrdma_mqe *mqe,
				 void *payload_va)
{
	int status;
	struct ocrdma_mbx_rsp *rsp = payload_va;

	if ((mqe->hdr.spcl_sge_cnt_emb & OCRDMA_MQE_HDR_EMB_MASK) >>
				OCRDMA_MQE_HDR_EMB_SHIFT)
		BUG();

	status = ocrdma_mbx_cmd(dev, mqe);
	if (!status)
		/* For non embedded, only CQE failures are handled in
		 * ocrdma_mbx_cmd. We need to check for RSP errors.
		 */
		if (rsp->status & OCRDMA_MBX_RSP_STATUS_MASK)
			status = ocrdma_get_mbx_errno(rsp->status);

	if (status)
		pr_err("opcode=0x%x, subsystem=0x%x\n",
		       (rsp->subsys_op & OCRDMA_MBX_RSP_OPCODE_MASK) >>
			OCRDMA_MBX_RSP_OPCODE_SHIFT,
			(rsp->subsys_op & OCRDMA_MBX_RSP_SUBSYS_MASK) >>
			OCRDMA_MBX_RSP_SUBSYS_SHIFT);
	return status;
}