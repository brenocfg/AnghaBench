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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ last_cb_index; } ;
struct ipw_priv {TYPE_1__ sram_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_FW (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_FW_INFO (char*,...) ; 
 int /*<<< orphan*/  IPW_RESET_REG ; 
 int IPW_RESET_REG_MASTER_DISABLED ; 
 int IPW_RESET_REG_STOP_MASTER ; 
 int /*<<< orphan*/  ipw_fw_dma_abort (struct ipw_priv*) ; 
 scalar_t__ ipw_fw_dma_command_block_index (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_fw_dma_dump_command_block (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_set_bit (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ipw_fw_dma_wait(struct ipw_priv *priv)
{
	u32 current_index = 0, previous_index;
	u32 watchdog = 0;

	IPW_DEBUG_FW(">> :\n");

	current_index = ipw_fw_dma_command_block_index(priv);
	IPW_DEBUG_FW_INFO("sram_desc.last_cb_index:0x%08X\n",
			  (int)priv->sram_desc.last_cb_index);

	while (current_index < priv->sram_desc.last_cb_index) {
		udelay(50);
		previous_index = current_index;
		current_index = ipw_fw_dma_command_block_index(priv);

		if (previous_index < current_index) {
			watchdog = 0;
			continue;
		}
		if (++watchdog > 400) {
			IPW_DEBUG_FW_INFO("Timeout\n");
			ipw_fw_dma_dump_command_block(priv);
			ipw_fw_dma_abort(priv);
			return -1;
		}
	}

	ipw_fw_dma_abort(priv);

	/*Disable the DMA in the CSR register */
	ipw_set_bit(priv, IPW_RESET_REG,
		    IPW_RESET_REG_MASTER_DISABLED | IPW_RESET_REG_STOP_MASTER);

	IPW_DEBUG_FW("<< dmaWaitSync\n");
	return 0;
}