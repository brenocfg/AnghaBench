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
struct icp_qat_fw_loader_handle {int dummy; } ;
typedef  enum icp_qat_uof_regtype { ____Placeholder_icp_qat_uof_regtype } icp_qat_uof_regtype ;

/* Variables and functions */
 int EFAULT ; 
#define  ICP_DR_ABS 144 
#define  ICP_DR_RD_ABS 143 
#define  ICP_DR_RD_REL 142 
#define  ICP_DR_REL 141 
#define  ICP_DR_WR_ABS 140 
#define  ICP_DR_WR_REL 139 
#define  ICP_GPA_ABS 138 
#define  ICP_GPA_REL 137 
#define  ICP_GPB_ABS 136 
#define  ICP_GPB_REL 135 
#define  ICP_NEIGH_REL 134 
#define  ICP_SR_ABS 133 
#define  ICP_SR_RD_ABS 132 
#define  ICP_SR_RD_REL 131 
#define  ICP_SR_REL 130 
#define  ICP_SR_WR_ABS 129 
#define  ICP_SR_WR_REL 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int qat_hal_init_gpr (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int,unsigned short,unsigned int) ; 
 int qat_hal_init_nn (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,unsigned short,unsigned int) ; 
 int qat_hal_init_rd_xfer (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int,unsigned short,unsigned int) ; 
 int qat_hal_init_wr_xfer (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int,unsigned short,unsigned int) ; 

__attribute__((used)) static int qat_uclo_init_reg(struct icp_qat_fw_loader_handle *handle,
			     unsigned char ae, unsigned char ctx_mask,
			     enum icp_qat_uof_regtype reg_type,
			     unsigned short reg_addr, unsigned int value)
{
	switch (reg_type) {
	case ICP_GPA_ABS:
	case ICP_GPB_ABS:
		ctx_mask = 0;
		/* fall through */
	case ICP_GPA_REL:
	case ICP_GPB_REL:
		return qat_hal_init_gpr(handle, ae, ctx_mask, reg_type,
					reg_addr, value);
	case ICP_SR_ABS:
	case ICP_DR_ABS:
	case ICP_SR_RD_ABS:
	case ICP_DR_RD_ABS:
		ctx_mask = 0;
		/* fall through */
	case ICP_SR_REL:
	case ICP_DR_REL:
	case ICP_SR_RD_REL:
	case ICP_DR_RD_REL:
		return qat_hal_init_rd_xfer(handle, ae, ctx_mask, reg_type,
					    reg_addr, value);
	case ICP_SR_WR_ABS:
	case ICP_DR_WR_ABS:
		ctx_mask = 0;
		/* fall through */
	case ICP_SR_WR_REL:
	case ICP_DR_WR_REL:
		return qat_hal_init_wr_xfer(handle, ae, ctx_mask, reg_type,
					    reg_addr, value);
	case ICP_NEIGH_REL:
		return qat_hal_init_nn(handle, ae, ctx_mask, reg_addr, value);
	default:
		pr_err("QAT: UOF uses not supported reg type 0x%x\n", reg_type);
		return -EFAULT;
	}
	return 0;
}