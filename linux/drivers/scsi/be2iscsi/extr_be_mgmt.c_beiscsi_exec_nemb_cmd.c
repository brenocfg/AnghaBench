#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct be_ctrl_info {TYPE_2__* pdev; int /*<<< orphan*/  mbox_lock; TYPE_1__* ptag_state; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_sge {void* len; void* pa_lo; void* pa_hi; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  dma; int /*<<< orphan*/  va; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {void (* cbfn ) (struct beiscsi_hba*,unsigned int) ;struct be_dma_mem tag_mem_state; int /*<<< orphan*/  tag_state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MCC_TAG_STATE_ASYNC ; 
 struct be_mcc_wrb* alloc_mcc_wrb (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int /*<<< orphan*/ ,int,int) ; 
 int beiscsi_mccq_compl_wait (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,struct be_dma_mem*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_sge* nonembedded_sgl (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_exec_nemb_cmd(struct beiscsi_hba *phba,
				 struct be_dma_mem *nonemb_cmd,
				 void (*cbfn)(struct beiscsi_hba *,
					      unsigned int),
				 void *resp_buf, u32 resp_buf_len)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	struct be_sge *sge;
	unsigned int tag;
	int rc = 0;

	mutex_lock(&ctrl->mbox_lock);
	wrb = alloc_mcc_wrb(phba, &tag);
	if (!wrb) {
		mutex_unlock(&ctrl->mbox_lock);
		rc = -ENOMEM;
		goto free_cmd;
	}

	sge = nonembedded_sgl(wrb);
	be_wrb_hdr_prepare(wrb, nonemb_cmd->size, false, 1);
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd->dma));
	sge->pa_lo = cpu_to_le32(lower_32_bits(nonemb_cmd->dma));
	sge->len = cpu_to_le32(nonemb_cmd->size);

	if (cbfn) {
		struct be_dma_mem *tag_mem;

		set_bit(MCC_TAG_STATE_ASYNC, &ctrl->ptag_state[tag].tag_state);
		ctrl->ptag_state[tag].cbfn = cbfn;
		tag_mem = &phba->ctrl.ptag_state[tag].tag_mem_state;

		/* store DMA mem to be freed in callback */
		tag_mem->size = nonemb_cmd->size;
		tag_mem->va = nonemb_cmd->va;
		tag_mem->dma = nonemb_cmd->dma;
	}
	be_mcc_notify(phba, tag);
	mutex_unlock(&ctrl->mbox_lock);

	/* with cbfn set, its async cmd, don't wait */
	if (cbfn)
		return 0;

	rc = beiscsi_mccq_compl_wait(phba, tag, NULL, nonemb_cmd);

	/* copy the response, if any */
	if (resp_buf)
		memcpy(resp_buf, nonemb_cmd->va, resp_buf_len);
	/**
	 * This is special case of NTWK_GET_IF_INFO where the size of
	 * response is not known. beiscsi_if_get_info checks the return
	 * value to free DMA buffer.
	 */
	if (rc == -EAGAIN)
		return rc;

	/**
	 * If FW is busy that is driver timed out, DMA buffer is saved with
	 * the tag, only when the cmd completes this buffer is freed.
	 */
	if (rc == -EBUSY)
		return rc;

free_cmd:
	dma_free_coherent(&ctrl->pdev->dev, nonemb_cmd->size,
			    nonemb_cmd->va, nonemb_cmd->dma);
	return rc;
}