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
struct fw_pfvf_cmd {void* r_caps_to_nethctrl; void* tc_to_nexactf; void* type_to_neq; void* niqflint_niq; void* retval_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int FW_LEN16 (struct fw_pfvf_cmd) ; 
 int /*<<< orphan*/  FW_PFVF_CMD ; 
 int FW_PFVF_CMD_CMASK_V (unsigned int) ; 
 int FW_PFVF_CMD_NEQ_V (unsigned int) ; 
 int FW_PFVF_CMD_NETHCTRL_V (unsigned int) ; 
 int FW_PFVF_CMD_NEXACTF_V (unsigned int) ; 
 int FW_PFVF_CMD_NIQFLINT_V (unsigned int) ; 
 int FW_PFVF_CMD_NIQ_V (unsigned int) ; 
 int FW_PFVF_CMD_NVI_V (unsigned int) ; 
 int FW_PFVF_CMD_PFN_V (unsigned int) ; 
 int FW_PFVF_CMD_PMASK_V (unsigned int) ; 
 int FW_PFVF_CMD_R_CAPS_V (unsigned int) ; 
 int FW_PFVF_CMD_TC_V (unsigned int) ; 
 int FW_PFVF_CMD_VFN_V (unsigned int) ; 
 int FW_PFVF_CMD_WX_CAPS_V (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_pfvf_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_pfvf_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_cfg_pfvf(struct adapter *adap, unsigned int mbox, unsigned int pf,
		unsigned int vf, unsigned int txq, unsigned int txq_eth_ctrl,
		unsigned int rxqi, unsigned int rxq, unsigned int tc,
		unsigned int vi, unsigned int cmask, unsigned int pmask,
		unsigned int nexact, unsigned int rcaps, unsigned int wxcaps)
{
	struct fw_pfvf_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) | FW_CMD_REQUEST_F |
				  FW_CMD_WRITE_F | FW_PFVF_CMD_PFN_V(pf) |
				  FW_PFVF_CMD_VFN_V(vf));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.niqflint_niq = cpu_to_be32(FW_PFVF_CMD_NIQFLINT_V(rxqi) |
				     FW_PFVF_CMD_NIQ_V(rxq));
	c.type_to_neq = cpu_to_be32(FW_PFVF_CMD_CMASK_V(cmask) |
				    FW_PFVF_CMD_PMASK_V(pmask) |
				    FW_PFVF_CMD_NEQ_V(txq));
	c.tc_to_nexactf = cpu_to_be32(FW_PFVF_CMD_TC_V(tc) |
				      FW_PFVF_CMD_NVI_V(vi) |
				      FW_PFVF_CMD_NEXACTF_V(nexact));
	c.r_caps_to_nethctrl = cpu_to_be32(FW_PFVF_CMD_R_CAPS_V(rcaps) |
					FW_PFVF_CMD_WX_CAPS_V(wxcaps) |
					FW_PFVF_CMD_NETHCTRL_V(txq_eth_ctrl));
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}