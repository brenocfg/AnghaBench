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
typedef  int u32 ;
struct TYPE_3__ {int ctrl_to_fn; int r; int /*<<< orphan*/ * data; int /*<<< orphan*/  select_naccess; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int /*<<< orphan*/  mbox; int /*<<< orphan*/  pf; } ;
typedef  int /*<<< orphan*/  ldst_cmd ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_FUNC_PCIE ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LDST_CMD_ADDRSPACE_V (int /*<<< orphan*/ ) ; 
 int FW_LDST_CMD_FN_V (int /*<<< orphan*/ ) ; 
 int FW_LDST_CMD_LC_F ; 
 int /*<<< orphan*/  FW_LDST_CMD_NACCESS_V (int) ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_hw_pci_read_cfg4 (struct adapter*,int,int*) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 

u32 t4_read_pcie_cfg4(struct adapter *adap, int reg)
{
	u32 val, ldst_addrspace;

	/* If fw_attach != 0, construct and send the Firmware LDST Command to
	 * retrieve the specified PCI-E Configuration Space register.
	 */
	struct fw_ldst_cmd ldst_cmd;
	int ret;

	memset(&ldst_cmd, 0, sizeof(ldst_cmd));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_FUNC_PCIE);
	ldst_cmd.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					       FW_CMD_REQUEST_F |
					       FW_CMD_READ_F |
					       ldst_addrspace);
	ldst_cmd.cycles_to_len16 = cpu_to_be32(FW_LEN16(ldst_cmd));
	ldst_cmd.u.pcie.select_naccess = FW_LDST_CMD_NACCESS_V(1);
	ldst_cmd.u.pcie.ctrl_to_fn =
		(FW_LDST_CMD_LC_F | FW_LDST_CMD_FN_V(adap->pf));
	ldst_cmd.u.pcie.r = reg;

	/* If the LDST Command succeeds, return the result, otherwise
	 * fall through to reading it directly ourselves ...
	 */
	ret = t4_wr_mbox(adap, adap->mbox, &ldst_cmd, sizeof(ldst_cmd),
			 &ldst_cmd);
	if (ret == 0)
		val = be32_to_cpu(ldst_cmd.u.pcie.data[0]);
	else
		/* Read the desired Configuration Space register via the PCI-E
		 * Backdoor mechanism.
		 */
		t4_hw_pci_read_cfg4(adap, reg, &val);
	return val;
}