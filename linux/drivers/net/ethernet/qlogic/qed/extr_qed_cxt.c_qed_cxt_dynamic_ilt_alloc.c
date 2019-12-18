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
struct TYPE_11__ {scalar_t__ flags1; } ;
struct TYPE_12__ {TYPE_4__ tdif_context; } ;
union type1_task_context {TYPE_5__ roce_ctx; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_8__ {size_t val; } ;
struct qed_ilt_client_cfg {TYPE_1__ p_size; struct qed_ilt_cli_blk* pf_blks; } ;
struct qed_ilt_cli_blk {size_t start_line; int /*<<< orphan*/  real_size_in_page; } ;
struct qed_hwfn {int b_rdma_enabled_in_prs; TYPE_7__* p_cxt_mngr; int /*<<< orphan*/  rdma_prs_search_reg; TYPE_3__* cdev; } ;
typedef  int /*<<< orphan*/  ilt_hw_entry ;
typedef  enum qed_cxt_elem_type { ____Placeholder_qed_cxt_elem_type } qed_cxt_elem_type ;
typedef  int dma_addr_t ;
struct TYPE_14__ {size_t pf_start_line; int /*<<< orphan*/  mutex; TYPE_6__* ilt_shadow; struct qed_ilt_client_cfg* clients; } ;
struct TYPE_13__ {int p_phys; int /*<<< orphan*/  size; void* p_virt; } ;
struct TYPE_10__ {TYPE_2__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CDUC_BLK ; 
 size_t CDUT_SEG_BLK (int /*<<< orphan*/ ) ; 
 size_t CONN_CXT_SIZE (struct qed_hwfn*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t ILT_CLI_CDUC ; 
 size_t ILT_CLI_CDUT ; 
 size_t ILT_CLI_TSDM ; 
 size_t ILT_ENTRY_IN_REGS ; 
 int /*<<< orphan*/  ILT_ENTRY_PHY_ADDR ; 
 int /*<<< orphan*/  ILT_ENTRY_VALID ; 
 size_t ILT_PAGE_IN_BYTES (size_t) ; 
 size_t ILT_REG_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  PRS_REG_ROCE_DEST_QP_MAX_PF ; 
 size_t PSWRQ2_REG_ILT_MEMORY ; 
 int /*<<< orphan*/  QED_CXT_ROCE_TID_SEG ; 
#define  QED_ELEM_CXT 130 
#define  QED_ELEM_SRQ 129 
#define  QED_ELEM_TASK 128 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 size_t SRQ_BLK ; 
 size_t SRQ_CXT_SIZE ; 
 int /*<<< orphan*/  TDIF_TASK_CONTEXT_REF_TAG_MASK ; 
 size_t TYPE1_TASK_CXT_SIZE (struct qed_hwfn*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_dmae_host2grc (struct qed_hwfn*,struct qed_ptt*,scalar_t__,size_t,int,int /*<<< orphan*/ *) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

int
qed_cxt_dynamic_ilt_alloc(struct qed_hwfn *p_hwfn,
			  enum qed_cxt_elem_type elem_type, u32 iid)
{
	u32 reg_offset, shadow_line, elem_size, hw_p_size, elems_per_p, line;
	struct qed_ilt_client_cfg *p_cli;
	struct qed_ilt_cli_blk *p_blk;
	struct qed_ptt *p_ptt;
	dma_addr_t p_phys;
	u64 ilt_hw_entry;
	void *p_virt;
	int rc = 0;

	switch (elem_type) {
	case QED_ELEM_CXT:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];
		elem_size = CONN_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUC_BLK];
		break;
	case QED_ELEM_SRQ:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_TSDM];
		elem_size = SRQ_CXT_SIZE;
		p_blk = &p_cli->pf_blks[SRQ_BLK];
		break;
	case QED_ELEM_TASK:
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUT];
		elem_size = TYPE1_TASK_CXT_SIZE(p_hwfn);
		p_blk = &p_cli->pf_blks[CDUT_SEG_BLK(QED_CXT_ROCE_TID_SEG)];
		break;
	default:
		DP_NOTICE(p_hwfn, "-EINVALID elem type = %d", elem_type);
		return -EINVAL;
	}

	/* Calculate line in ilt */
	hw_p_size = p_cli->p_size.val;
	elems_per_p = ILT_PAGE_IN_BYTES(hw_p_size) / elem_size;
	line = p_blk->start_line + (iid / elems_per_p);
	shadow_line = line - p_hwfn->p_cxt_mngr->pf_start_line;

	/* If line is already allocated, do nothing, otherwise allocate it and
	 * write it to the PSWRQ2 registers.
	 * This section can be run in parallel from different contexts and thus
	 * a mutex protection is needed.
	 */

	mutex_lock(&p_hwfn->p_cxt_mngr->mutex);

	if (p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_virt)
		goto out0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_NOTICE(p_hwfn,
			  "QED_TIME_OUT on ptt acquire - dynamic allocation");
		rc = -EBUSY;
		goto out0;
	}

	p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    p_blk->real_size_in_page, &p_phys,
				    GFP_KERNEL);
	if (!p_virt) {
		rc = -ENOMEM;
		goto out1;
	}

	/* configuration of refTagMask to 0xF is required for RoCE DIF MR only,
	 * to compensate for a HW bug, but it is configured even if DIF is not
	 * enabled. This is harmless and allows us to avoid a dedicated API. We
	 * configure the field for all of the contexts on the newly allocated
	 * page.
	 */
	if (elem_type == QED_ELEM_TASK) {
		u32 elem_i;
		u8 *elem_start = (u8 *)p_virt;
		union type1_task_context *elem;

		for (elem_i = 0; elem_i < elems_per_p; elem_i++) {
			elem = (union type1_task_context *)elem_start;
			SET_FIELD(elem->roce_ctx.tdif_context.flags1,
				  TDIF_TASK_CONTEXT_REF_TAG_MASK, 0xf);
			elem_start += TYPE1_TASK_CXT_SIZE(p_hwfn);
		}
	}

	p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_virt = p_virt;
	p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_phys = p_phys;
	p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].size =
	    p_blk->real_size_in_page;

	/* compute absolute offset */
	reg_offset = PSWRQ2_REG_ILT_MEMORY +
	    (line * ILT_REG_SIZE_IN_BYTES * ILT_ENTRY_IN_REGS);

	ilt_hw_entry = 0;
	SET_FIELD(ilt_hw_entry, ILT_ENTRY_VALID, 1ULL);
	SET_FIELD(ilt_hw_entry,
		  ILT_ENTRY_PHY_ADDR,
		  (p_hwfn->p_cxt_mngr->ilt_shadow[shadow_line].p_phys >> 12));

	/* Write via DMAE since the PSWRQ2_REG_ILT_MEMORY line is a wide-bus */
	qed_dmae_host2grc(p_hwfn, p_ptt, (u64) (uintptr_t)&ilt_hw_entry,
			  reg_offset, sizeof(ilt_hw_entry) / sizeof(u32),
			  NULL);

	if (elem_type == QED_ELEM_CXT) {
		u32 last_cid_allocated = (1 + (iid / elems_per_p)) *
		    elems_per_p;

		/* Update the relevant register in the parser */
		qed_wr(p_hwfn, p_ptt, PRS_REG_ROCE_DEST_QP_MAX_PF,
		       last_cid_allocated - 1);

		if (!p_hwfn->b_rdma_enabled_in_prs) {
			/* Enable RDMA search */
			qed_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 1);
			p_hwfn->b_rdma_enabled_in_prs = true;
		}
	}

out1:
	qed_ptt_release(p_hwfn, p_ptt);
out0:
	mutex_unlock(&p_hwfn->p_cxt_mngr->mutex);

	return rc;
}