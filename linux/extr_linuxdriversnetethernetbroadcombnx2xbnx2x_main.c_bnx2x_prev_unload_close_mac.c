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
struct bnx2x_mac_vals {int bmac_addr; int* bmac_val; int emac_addr; int xmac_addr; void* xmac_val; void* emac_val; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BIGMAC2_REGISTER_BMAC_CONTROL ; 
 int BIGMAC_REGISTER_BMAC_CONTROL ; 
 int BMAC_CONTROL_RX_ENABLE ; 
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*) ; 
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E3 (struct bnx2x*) ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 int MISC_REGISTERS_RESET_REG_2_RST_BMAC0 ; 
 int MISC_REGISTERS_RESET_REG_2_XMAC ; 
 int MISC_REG_RESET_REG_2 ; 
 int NIG_REG_BMAC0_REGS_OUT_EN ; 
 int NIG_REG_INGRESS_BMAC0_MEM ; 
 int NIG_REG_INGRESS_BMAC1_MEM ; 
 int NIG_REG_NIG_EMAC0_EN ; 
 void* REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int XMAC_REG_CTRL ; 
 int XMAC_REG_PFC_CTRL_HI ; 
 int bnx2x_prev_unload_close_umac (struct bnx2x*,int,int,struct bnx2x_mac_vals*) ; 
 int /*<<< orphan*/  memset (struct bnx2x_mac_vals*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void bnx2x_prev_unload_close_mac(struct bnx2x *bp,
					struct bnx2x_mac_vals *vals)
{
	u32 val, base_addr, offset, mask, reset_reg;
	bool mac_stopped = false;
	u8 port = BP_PORT(bp);

	/* reset addresses as they also mark which values were changed */
	memset(vals, 0, sizeof(*vals));

	reset_reg = REG_RD(bp, MISC_REG_RESET_REG_2);

	if (!CHIP_IS_E3(bp)) {
		val = REG_RD(bp, NIG_REG_BMAC0_REGS_OUT_EN + port * 4);
		mask = MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port;
		if ((mask & reset_reg) && val) {
			u32 wb_data[2];
			BNX2X_DEV_INFO("Disable bmac Rx\n");
			base_addr = BP_PORT(bp) ? NIG_REG_INGRESS_BMAC1_MEM
						: NIG_REG_INGRESS_BMAC0_MEM;
			offset = CHIP_IS_E2(bp) ? BIGMAC2_REGISTER_BMAC_CONTROL
						: BIGMAC_REGISTER_BMAC_CONTROL;

			/*
			 * use rd/wr since we cannot use dmae. This is safe
			 * since MCP won't access the bus due to the request
			 * to unload, and no function on the path can be
			 * loaded at this time.
			 */
			wb_data[0] = REG_RD(bp, base_addr + offset);
			wb_data[1] = REG_RD(bp, base_addr + offset + 0x4);
			vals->bmac_addr = base_addr + offset;
			vals->bmac_val[0] = wb_data[0];
			vals->bmac_val[1] = wb_data[1];
			wb_data[0] &= ~BMAC_CONTROL_RX_ENABLE;
			REG_WR(bp, vals->bmac_addr, wb_data[0]);
			REG_WR(bp, vals->bmac_addr + 0x4, wb_data[1]);
		}
		BNX2X_DEV_INFO("Disable emac Rx\n");
		vals->emac_addr = NIG_REG_NIG_EMAC0_EN + BP_PORT(bp)*4;
		vals->emac_val = REG_RD(bp, vals->emac_addr);
		REG_WR(bp, vals->emac_addr, 0);
		mac_stopped = true;
	} else {
		if (reset_reg & MISC_REGISTERS_RESET_REG_2_XMAC) {
			BNX2X_DEV_INFO("Disable xmac Rx\n");
			base_addr = BP_PORT(bp) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
			val = REG_RD(bp, base_addr + XMAC_REG_PFC_CTRL_HI);
			REG_WR(bp, base_addr + XMAC_REG_PFC_CTRL_HI,
			       val & ~(1 << 1));
			REG_WR(bp, base_addr + XMAC_REG_PFC_CTRL_HI,
			       val | (1 << 1));
			vals->xmac_addr = base_addr + XMAC_REG_CTRL;
			vals->xmac_val = REG_RD(bp, vals->xmac_addr);
			REG_WR(bp, vals->xmac_addr, 0);
			mac_stopped = true;
		}

		mac_stopped |= bnx2x_prev_unload_close_umac(bp, 0,
							    reset_reg, vals);
		mac_stopped |= bnx2x_prev_unload_close_umac(bp, 1,
							    reset_reg, vals);
	}

	if (mac_stopped)
		msleep(20);
}