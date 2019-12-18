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
typedef  size_t u32 ;
struct TYPE_2__ {size_t last_cb_index; int /*<<< orphan*/ * cb_list; } ;
struct ipw_priv {TYPE_1__ sram_desc; } ;

/* Variables and functions */
 size_t DMA_CB_START ; 
 size_t DMA_CONTROL_SMALL_CB_CONST_VALUE ; 
 int /*<<< orphan*/  IPW_DEBUG_FW (char*) ; 
 int /*<<< orphan*/  IPW_DMA_I_DMA_CONTROL ; 
 int /*<<< orphan*/  IPW_RESET_REG ; 
 int IPW_RESET_REG_MASTER_DISABLED ; 
 int IPW_RESET_REG_STOP_MASTER ; 
 int /*<<< orphan*/  ipw_clear_bit (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipw_fw_dma_write_command_block (struct ipw_priv*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int ipw_fw_dma_kick(struct ipw_priv *priv)
{
	u32 control = 0;
	u32 index = 0;

	IPW_DEBUG_FW(">> :\n");

	for (index = 0; index < priv->sram_desc.last_cb_index; index++)
		ipw_fw_dma_write_command_block(priv, index,
					       &priv->sram_desc.cb_list[index]);

	/* Enable the DMA in the CSR register */
	ipw_clear_bit(priv, IPW_RESET_REG,
		      IPW_RESET_REG_MASTER_DISABLED |
		      IPW_RESET_REG_STOP_MASTER);

	/* Set the Start bit. */
	control = DMA_CONTROL_SMALL_CB_CONST_VALUE | DMA_CB_START;
	ipw_write_reg32(priv, IPW_DMA_I_DMA_CONTROL, control);

	IPW_DEBUG_FW("<< :\n");
	return 0;
}