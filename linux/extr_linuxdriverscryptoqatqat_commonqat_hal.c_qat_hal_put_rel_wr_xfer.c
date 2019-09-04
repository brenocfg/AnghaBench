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
typedef  int uint64_t ;
struct icp_qat_fw_loader_handle {int dummy; } ;
typedef  enum icp_qat_uof_regtype { ____Placeholder_icp_qat_uof_regtype } icp_qat_uof_regtype ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 unsigned short BAD_REGADDR ; 
 unsigned int CE_INUSE_CONTEXTS ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 int EINVAL ; 
 int ICP_GPB_REL ; 
 int ICP_NO_DEST ; 
 int /*<<< orphan*/  pr_err (char*,unsigned short) ; 
 int qat_hal_exec_micro_inst (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int*,int const,int const,unsigned short const,int /*<<< orphan*/ *) ; 
 unsigned short qat_hal_get_reg_addr (int,unsigned short const) ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_rd_rel_reg (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int,unsigned short const,unsigned int*) ; 
 int /*<<< orphan*/  qat_hal_wr_rel_reg (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int,unsigned short const,unsigned int) ; 

__attribute__((used)) static int qat_hal_put_rel_wr_xfer(struct icp_qat_fw_loader_handle *handle,
				   unsigned char ae, unsigned char ctx,
				   enum icp_qat_uof_regtype reg_type,
				   unsigned short reg_num, unsigned int data)
{
	unsigned int gprval, ctx_enables;
	unsigned short src_hiaddr, src_lowaddr, gpr_addr, xfr_addr, data16hi,
	    data16low;
	unsigned short reg_mask;
	int status = 0;
	uint64_t micro_inst[] = {
		0x0F440000000ull,
		0x0F040000000ull,
		0x0A000000000ull,
		0x0F0000C0300ull,
		0x0E000010000ull
	};
	const int num_inst = ARRAY_SIZE(micro_inst), code_off = 1;
	const unsigned short gprnum = 0, dly = num_inst * 0x5;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	if (CE_INUSE_CONTEXTS & ctx_enables) {
		if (ctx & 0x1) {
			pr_err("QAT: 4-ctx mode,ctx=0x%x\n", ctx);
			return -EINVAL;
		}
		reg_mask = (unsigned short)~0x1f;
	} else {
		reg_mask = (unsigned short)~0xf;
	}
	if (reg_num & reg_mask)
		return -EINVAL;
	xfr_addr = qat_hal_get_reg_addr(reg_type, reg_num);
	if (xfr_addr == BAD_REGADDR) {
		pr_err("QAT: bad xfrAddr=0x%x\n", xfr_addr);
		return -EINVAL;
	}
	qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPB_REL, gprnum, &gprval);
	gpr_addr = qat_hal_get_reg_addr(ICP_GPB_REL, gprnum);
	data16low = 0xffff & data;
	data16hi = 0xffff & (data >> 0x10);
	src_hiaddr = qat_hal_get_reg_addr(ICP_NO_DEST,
					  (unsigned short)(0xff & data16hi));
	src_lowaddr = qat_hal_get_reg_addr(ICP_NO_DEST,
					   (unsigned short)(0xff & data16low));
	micro_inst[0] = micro_inst[0x0] | ((data16hi >> 8) << 20) |
	    ((gpr_addr & 0x3ff) << 10) | (src_hiaddr & 0x3ff);
	micro_inst[1] = micro_inst[0x1] | ((data16low >> 8) << 20) |
	    ((gpr_addr & 0x3ff) << 10) | (src_lowaddr & 0x3ff);
	micro_inst[0x2] = micro_inst[0x2] |
	    ((xfr_addr & 0x3ff) << 20) | ((gpr_addr & 0x3ff) << 10);
	status = qat_hal_exec_micro_inst(handle, ae, ctx, micro_inst, num_inst,
					 code_off, dly, NULL);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPB_REL, gprnum, gprval);
	return status;
}