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
typedef  int /*<<< orphan*/  u32 ;
struct pf_resources {int /*<<< orphan*/  nethctrl; int /*<<< orphan*/  wx_caps; int /*<<< orphan*/  r_caps; int /*<<< orphan*/  nexactf; int /*<<< orphan*/  nvi; int /*<<< orphan*/  tc; int /*<<< orphan*/  pmask; int /*<<< orphan*/  neq; int /*<<< orphan*/  niq; int /*<<< orphan*/  niqflint; } ;
struct fw_pfvf_cmd {int /*<<< orphan*/  r_caps_to_nethctrl; int /*<<< orphan*/  tc_to_nexactf; int /*<<< orphan*/  type_to_neq; int /*<<< orphan*/  niqflint_niq; void* retval_len16; void* op_to_vfn; } ;
struct TYPE_2__ {struct pf_resources pfres; } ;
struct adapter {int /*<<< orphan*/  mbox; int /*<<< orphan*/  pf; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_pfvf_cmd) ; 
 int /*<<< orphan*/  FW_PFVF_CMD ; 
 int /*<<< orphan*/  FW_PFVF_CMD_NEQ_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_NETHCTRL_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_NEXACTF_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_NIQFLINT_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_NIQ_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_NVI_G (int /*<<< orphan*/ ) ; 
 int FW_PFVF_CMD_PFN_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_PMASK_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_R_CAPS_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_TC_G (int /*<<< orphan*/ ) ; 
 int FW_PFVF_CMD_VFN_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PFVF_CMD_WX_CAPS_G (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_pfvf_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_pfvf_cmd*,int,struct fw_pfvf_cmd*) ; 

int t4_get_pfres(struct adapter *adapter)
{
	struct pf_resources *pfres = &adapter->params.pfres;
	struct fw_pfvf_cmd cmd, rpl;
	int v;
	u32 word;

	/* Execute PFVF Read command to get VF resource limits; bail out early
	 * with error on command failure.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PFVF_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_READ_F |
				    FW_PFVF_CMD_PFN_V(adapter->pf) |
				    FW_PFVF_CMD_VFN_V(0));
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4_wr_mbox(adapter, adapter->mbox, &cmd, sizeof(cmd), &rpl);
	if (v != FW_SUCCESS)
		return v;

	/* Extract PF resource limits and return success.
	 */
	word = be32_to_cpu(rpl.niqflint_niq);
	pfres->niqflint = FW_PFVF_CMD_NIQFLINT_G(word);
	pfres->niq = FW_PFVF_CMD_NIQ_G(word);

	word = be32_to_cpu(rpl.type_to_neq);
	pfres->neq = FW_PFVF_CMD_NEQ_G(word);
	pfres->pmask = FW_PFVF_CMD_PMASK_G(word);

	word = be32_to_cpu(rpl.tc_to_nexactf);
	pfres->tc = FW_PFVF_CMD_TC_G(word);
	pfres->nvi = FW_PFVF_CMD_NVI_G(word);
	pfres->nexactf = FW_PFVF_CMD_NEXACTF_G(word);

	word = be32_to_cpu(rpl.r_caps_to_nethctrl);
	pfres->r_caps = FW_PFVF_CMD_R_CAPS_G(word);
	pfres->wx_caps = FW_PFVF_CMD_WX_CAPS_G(word);
	pfres->nethctrl = FW_PFVF_CMD_NETHCTRL_G(word);

	return 0;
}