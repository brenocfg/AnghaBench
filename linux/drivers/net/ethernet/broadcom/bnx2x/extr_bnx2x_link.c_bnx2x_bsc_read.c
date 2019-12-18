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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct link_params {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int MCPR_IMC_COMMAND_ENABLE ; 
 int MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT ; 
 int MCPR_IMC_COMMAND_OPERATION_BITSHIFT ; 
 int MCPR_IMC_COMMAND_READ_OP ; 
 int MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT ; 
 int MCPR_IMC_COMMAND_WRITE_OP ; 
 scalar_t__ MCP_REG_MCPR_IMC_COMMAND ; 
 scalar_t__ MCP_REG_MCPR_IMC_DATAREG0 ; 
 scalar_t__ MCP_REG_MCPR_IMC_SLAVE_CONTROL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int REG_RD (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_bsc_module_sel (struct link_params*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bnx2x_bsc_read(struct link_params *params,
			  struct bnx2x *bp,
			  u8 sl_devid,
			  u16 sl_addr,
			  u8 lc_addr,
			  u8 xfer_cnt,
			  u32 *data_array)
{
	u32 val, i;
	int rc = 0;

	if (xfer_cnt > 16) {
		DP(NETIF_MSG_LINK, "invalid xfer_cnt %d. Max is 16 bytes\n",
					xfer_cnt);
		return -EINVAL;
	}
	bnx2x_bsc_module_sel(params);

	xfer_cnt = 16 - lc_addr;

	/* Enable the engine */
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	val |= MCPR_IMC_COMMAND_ENABLE;
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Program slave device ID */
	val = (sl_devid << 16) | sl_addr;
	REG_WR(bp, MCP_REG_MCPR_IMC_SLAVE_CONTROL, val);

	/* Start xfer with 0 byte to update the address pointer ???*/
	val = (MCPR_IMC_COMMAND_ENABLE) |
	      (MCPR_IMC_COMMAND_WRITE_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) | (0);
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Poll for completion */
	i = 0;
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	while (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) {
		udelay(10);
		val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
		if (i++ > 1000) {
			DP(NETIF_MSG_LINK, "wr 0 byte timed out after %d try\n",
								i);
			rc = -EFAULT;
			break;
		}
	}
	if (rc == -EFAULT)
		return rc;

	/* Start xfer with read op */
	val = (MCPR_IMC_COMMAND_ENABLE) |
		(MCPR_IMC_COMMAND_READ_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) |
		  (xfer_cnt);
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Poll for completion */
	i = 0;
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	while (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) {
		udelay(10);
		val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
		if (i++ > 1000) {
			DP(NETIF_MSG_LINK, "rd op timed out after %d try\n", i);
			rc = -EFAULT;
			break;
		}
	}
	if (rc == -EFAULT)
		return rc;

	for (i = (lc_addr >> 2); i < 4; i++) {
		data_array[i] = REG_RD(bp, (MCP_REG_MCPR_IMC_DATAREG0 + i*4));
#ifdef __BIG_ENDIAN
		data_array[i] = ((data_array[i] & 0x000000ff) << 24) |
				((data_array[i] & 0x0000ff00) << 8) |
				((data_array[i] & 0x00ff0000) >> 8) |
				((data_array[i] & 0xff000000) >> 24);
#endif
	}
	return rc;
}