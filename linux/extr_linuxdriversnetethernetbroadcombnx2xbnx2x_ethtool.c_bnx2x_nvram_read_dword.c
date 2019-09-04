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
typedef  int u32 ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int BNX2X_NVRAM_TIMEOUT_COUNT ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int,char*) ; 
 int EBUSY ; 
 int MCPR_NVM_ADDR_NVM_ADDR_VALUE ; 
 int MCPR_NVM_COMMAND_DOIT ; 
 int MCPR_NVM_COMMAND_DONE ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_ADDR ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_COMMAND ; 
 int /*<<< orphan*/  MCP_REG_MCPR_NVM_READ ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_nvram_read_dword(struct bnx2x *bp, u32 offset, __be32 *ret_val,
				  u32 cmd_flags)
{
	int count, i, rc;
	u32 val;

	/* build the command word */
	cmd_flags |= MCPR_NVM_COMMAND_DOIT;

	/* need to clear DONE bit separately */
	REG_WR(bp, MCP_REG_MCPR_NVM_COMMAND, MCPR_NVM_COMMAND_DONE);

	/* address of the NVRAM to read from */
	REG_WR(bp, MCP_REG_MCPR_NVM_ADDR,
	       (offset & MCPR_NVM_ADDR_NVM_ADDR_VALUE));

	/* issue a read command */
	REG_WR(bp, MCP_REG_MCPR_NVM_COMMAND, cmd_flags);

	/* adjust timeout for emulation/FPGA */
	count = BNX2X_NVRAM_TIMEOUT_COUNT;
	if (CHIP_REV_IS_SLOW(bp))
		count *= 100;

	/* wait for completion */
	*ret_val = 0;
	rc = -EBUSY;
	for (i = 0; i < count; i++) {
		udelay(5);
		val = REG_RD(bp, MCP_REG_MCPR_NVM_COMMAND);

		if (val & MCPR_NVM_COMMAND_DONE) {
			val = REG_RD(bp, MCP_REG_MCPR_NVM_READ);
			/* we read nvram data in cpu order
			 * but ethtool sees it as an array of bytes
			 * converting to big-endian will do the work
			 */
			*ret_val = cpu_to_be32(val);
			rc = 0;
			break;
		}
	}
	if (rc == -EBUSY)
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "nvram read timeout expired\n");
	return rc;
}