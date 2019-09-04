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
struct icp_qat_uof_init_regsym {unsigned int value; int init_type; int ctx; scalar_t__ reg_addr; int /*<<< orphan*/  reg_type; } ;
struct icp_qat_uclo_encapme {unsigned int init_regsym_num; struct icp_qat_uof_init_regsym* init_regsym; TYPE_1__* img_ptr; } ;
struct icp_qat_fw_loader_handle {int dummy; } ;
typedef  enum icp_qat_uof_regtype { ____Placeholder_icp_qat_uof_regtype } icp_qat_uof_regtype ;
struct TYPE_2__ {int /*<<< orphan*/  ae_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ICP_QAT_CTX_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ICP_QAT_UCLO_MAX_CTX ; 
#define  ICP_QAT_UOF_INIT_EXPR 131 
#define  ICP_QAT_UOF_INIT_EXPR_ENDIAN_SWAP 130 
#define  ICP_QAT_UOF_INIT_REG 129 
#define  ICP_QAT_UOF_INIT_REG_CTX 128 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  qat_uclo_init_reg (struct icp_qat_fw_loader_handle*,unsigned int,unsigned char,int,unsigned short,unsigned int) ; 

__attribute__((used)) static int qat_uclo_init_reg_sym(struct icp_qat_fw_loader_handle *handle,
				 unsigned int ae,
				 struct icp_qat_uclo_encapme *encap_ae)
{
	unsigned int i;
	unsigned char ctx_mask;
	struct icp_qat_uof_init_regsym *init_regsym;

	if (ICP_QAT_CTX_MODE(encap_ae->img_ptr->ae_mode) ==
	    ICP_QAT_UCLO_MAX_CTX)
		ctx_mask = 0xff;
	else
		ctx_mask = 0x55;

	for (i = 0; i < encap_ae->init_regsym_num; i++) {
		unsigned int exp_res;

		init_regsym = &encap_ae->init_regsym[i];
		exp_res = init_regsym->value;
		switch (init_regsym->init_type) {
		case ICP_QAT_UOF_INIT_REG:
			qat_uclo_init_reg(handle, ae, ctx_mask,
					  (enum icp_qat_uof_regtype)
					  init_regsym->reg_type,
					  (unsigned short)init_regsym->reg_addr,
					  exp_res);
			break;
		case ICP_QAT_UOF_INIT_REG_CTX:
			/* check if ctx is appropriate for the ctxMode */
			if (!((1 << init_regsym->ctx) & ctx_mask)) {
				pr_err("QAT: invalid ctx num = 0x%x\n",
				       init_regsym->ctx);
				return -EINVAL;
			}
			qat_uclo_init_reg(handle, ae,
					  (unsigned char)
					  (1 << init_regsym->ctx),
					  (enum icp_qat_uof_regtype)
					  init_regsym->reg_type,
					  (unsigned short)init_regsym->reg_addr,
					  exp_res);
			break;
		case ICP_QAT_UOF_INIT_EXPR:
			pr_err("QAT: INIT_EXPR feature not supported\n");
			return -EINVAL;
		case ICP_QAT_UOF_INIT_EXPR_ENDIAN_SWAP:
			pr_err("QAT: INIT_EXPR_ENDIAN_SWAP feature not supported\n");
			return -EINVAL;
		default:
			break;
		}
	}
	return 0;
}