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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rval; void* raddr; void* paddr_mmd; } ;
struct TYPE_4__ {TYPE_1__ mdio; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_MDIO ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LDST_CMD_ADDRSPACE_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_LDST_CMD_MMD_V (unsigned int) ; 
 unsigned int FW_LDST_CMD_PADDR_V (unsigned int) ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 

int t4_mdio_rd(struct adapter *adap, unsigned int mbox, unsigned int phy_addr,
	       unsigned int mmd, unsigned int reg, u16 *valp)
{
	int ret;
	u32 ldst_addrspace;
	struct fw_ldst_cmd c;

	memset(&c, 0, sizeof(c));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_MDIO);
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F | FW_CMD_READ_F |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.mdio.paddr_mmd = cpu_to_be16(FW_LDST_CMD_PADDR_V(phy_addr) |
					 FW_LDST_CMD_MMD_V(mmd));
	c.u.mdio.raddr = cpu_to_be16(reg);

	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	if (ret == 0)
		*valp = be16_to_cpu(c.u.mdio.rval);
	return ret;
}