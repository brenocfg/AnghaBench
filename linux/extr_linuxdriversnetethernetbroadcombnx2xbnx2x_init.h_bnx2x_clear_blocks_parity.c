#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  sts_clr_addr; } ;

/* Variables and functions */
 int AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY ; 
 int AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY ; 
 int AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY ; 
 int AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CSEM_REG_FAST_MEMORY ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  MISC_REG_AEU_AFTER_INVERT_4_MCP ; 
 scalar_t__ MISC_REG_AEU_CLR_LATCH_SIGNAL ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ SEM_FAST_REG_PARITY_RST ; 
 scalar_t__ TSEM_REG_FAST_MEMORY ; 
 scalar_t__ USEM_REG_FAST_MEMORY ; 
 scalar_t__ XSEM_REG_FAST_MEMORY ; 
 TYPE_1__* bnx2x_blocks_parity_data ; 
 int bnx2x_parity_reg_mask (struct bnx2x*,int) ; 

__attribute__((used)) static inline void bnx2x_clear_blocks_parity(struct bnx2x *bp)
{
	int i;
	u32 reg_val, mcp_aeu_bits =
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY |
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY |
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY |
		AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY;

	/* Clear SEM_FAST parities */
	REG_WR(bp, XSEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);
	REG_WR(bp, TSEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);
	REG_WR(bp, USEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);
	REG_WR(bp, CSEM_REG_FAST_MEMORY + SEM_FAST_REG_PARITY_RST, 0x1);

	for (i = 0; i < ARRAY_SIZE(bnx2x_blocks_parity_data); i++) {
		u32 reg_mask = bnx2x_parity_reg_mask(bp, i);

		if (reg_mask) {
			reg_val = REG_RD(bp, bnx2x_blocks_parity_data[i].
					 sts_clr_addr);
			if (reg_val & reg_mask)
				DP(NETIF_MSG_HW,
					    "Parity errors in %s: 0x%x\n",
					    bnx2x_blocks_parity_data[i].name,
					    reg_val & reg_mask);
		}
	}

	/* Check if there were parity attentions in MCP */
	reg_val = REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_4_MCP);
	if (reg_val & mcp_aeu_bits)
		DP(NETIF_MSG_HW, "Parity error in MCP: 0x%x\n",
		   reg_val & mcp_aeu_bits);

	/* Clear parity attentions in MCP:
	 * [7]  clears Latched rom_parity
	 * [8]  clears Latched ump_rx_parity
	 * [9]  clears Latched ump_tx_parity
	 * [10] clears Latched scpad_parity (both ports)
	 */
	REG_WR(bp, MISC_REG_AEU_CLR_LATCH_SIGNAL, 0x780);
}