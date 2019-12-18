#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct se_cmd {int t_task_lba; int prot_type; } ;
struct qla_tgt_cmd {TYPE_1__* tgt; struct se_cmd se_cmd; } ;
struct TYPE_7__ {TYPE_2__* tgt_ops; } ;
struct qla_hw_data {TYPE_3__ tgt; } ;
struct crc_context {int* app_tag_mask; int* ref_tag_mask; void* ref_tag; scalar_t__ app_tag; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_6__ {int (* get_dif_tags ) (struct qla_tgt_cmd*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* chk_dif_tags ) (int) ;} ;
struct TYPE_5__ {TYPE_4__* vha; } ;

/* Variables and functions */
 scalar_t__ IS_PI_UNINIT_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  PO_DIS_REF_TAG_VALD ; 
 int /*<<< orphan*/  PO_DIS_VALD_APP_ESC ; 
 int /*<<< orphan*/  PO_DIS_VALD_APP_REF_ESC ; 
#define  TARGET_DIF_TYPE0_PROT 131 
#define  TARGET_DIF_TYPE1_PROT 130 
#define  TARGET_DIF_TYPE2_PROT 129 
#define  TARGET_DIF_TYPE3_PROT 128 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  qla_tgt_ref_mask_check (struct se_cmd*) ; 
 int stub1 (struct qla_tgt_cmd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int) ; 

__attribute__((used)) static void
qla_tgt_set_dif_tags(struct qla_tgt_cmd *cmd, struct crc_context *ctx,
    uint16_t *pfw_prot_opts)
{
	struct se_cmd *se_cmd = &cmd->se_cmd;
	uint32_t lba = 0xffffffff & se_cmd->t_task_lba;
	scsi_qla_host_t *vha = cmd->tgt->vha;
	struct qla_hw_data *ha = vha->hw;
	uint32_t t32 = 0;

	/*
	 * wait till Mode Sense/Select cmd, modepage Ah, subpage 2
	 * have been immplemented by TCM, before AppTag is avail.
	 * Look for modesense_handlers[]
	 */
	ctx->app_tag = 0;
	ctx->app_tag_mask[0] = 0x0;
	ctx->app_tag_mask[1] = 0x0;

	if (IS_PI_UNINIT_CAPABLE(ha)) {
		if ((se_cmd->prot_type == TARGET_DIF_TYPE1_PROT) ||
		    (se_cmd->prot_type == TARGET_DIF_TYPE2_PROT))
			*pfw_prot_opts |= PO_DIS_VALD_APP_ESC;
		else if (se_cmd->prot_type == TARGET_DIF_TYPE3_PROT)
			*pfw_prot_opts |= PO_DIS_VALD_APP_REF_ESC;
	}

	t32 = ha->tgt.tgt_ops->get_dif_tags(cmd, pfw_prot_opts);

	switch (se_cmd->prot_type) {
	case TARGET_DIF_TYPE0_PROT:
		/*
		 * No check for ql2xenablehba_err_chk, as it
		 * would be an I/O error if hba tag generation
		 * is not done.
		 */
		ctx->ref_tag = cpu_to_le32(lba);
		/* enable ALL bytes of the ref tag */
		ctx->ref_tag_mask[0] = 0xff;
		ctx->ref_tag_mask[1] = 0xff;
		ctx->ref_tag_mask[2] = 0xff;
		ctx->ref_tag_mask[3] = 0xff;
		break;
	case TARGET_DIF_TYPE1_PROT:
	    /*
	     * For TYPE 1 protection: 16 bit GUARD tag, 32 bit
	     * REF tag, and 16 bit app tag.
	     */
	    ctx->ref_tag = cpu_to_le32(lba);
	    if (!qla_tgt_ref_mask_check(se_cmd) ||
		!(ha->tgt.tgt_ops->chk_dif_tags(t32))) {
		    *pfw_prot_opts |= PO_DIS_REF_TAG_VALD;
		    break;
	    }
	    /* enable ALL bytes of the ref tag */
	    ctx->ref_tag_mask[0] = 0xff;
	    ctx->ref_tag_mask[1] = 0xff;
	    ctx->ref_tag_mask[2] = 0xff;
	    ctx->ref_tag_mask[3] = 0xff;
	    break;
	case TARGET_DIF_TYPE2_PROT:
	    /*
	     * For TYPE 2 protection: 16 bit GUARD + 32 bit REF
	     * tag has to match LBA in CDB + N
	     */
	    ctx->ref_tag = cpu_to_le32(lba);
	    if (!qla_tgt_ref_mask_check(se_cmd) ||
		!(ha->tgt.tgt_ops->chk_dif_tags(t32))) {
		    *pfw_prot_opts |= PO_DIS_REF_TAG_VALD;
		    break;
	    }
	    /* enable ALL bytes of the ref tag */
	    ctx->ref_tag_mask[0] = 0xff;
	    ctx->ref_tag_mask[1] = 0xff;
	    ctx->ref_tag_mask[2] = 0xff;
	    ctx->ref_tag_mask[3] = 0xff;
	    break;
	case TARGET_DIF_TYPE3_PROT:
	    /* For TYPE 3 protection: 16 bit GUARD only */
	    *pfw_prot_opts |= PO_DIS_REF_TAG_VALD;
	    ctx->ref_tag_mask[0] = ctx->ref_tag_mask[1] =
		ctx->ref_tag_mask[2] = ctx->ref_tag_mask[3] = 0x00;
	    break;
	}
}