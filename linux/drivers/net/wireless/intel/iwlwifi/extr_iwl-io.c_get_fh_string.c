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

/* Variables and functions */
 int /*<<< orphan*/  FH_MEM_RCSR_CHNL0_CONFIG_REG ; 
 int /*<<< orphan*/  FH_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV ; 
 int /*<<< orphan*/  FH_MEM_RSSR_RX_STATUS_REG ; 
 int /*<<< orphan*/  FH_MEM_RSSR_SHARED_CTRL_REG ; 
 int /*<<< orphan*/  FH_RSCSR_CHNL0_RBDCB_BASE_REG ; 
 int /*<<< orphan*/  FH_RSCSR_CHNL0_STTS_WPTR_REG ; 
 int /*<<< orphan*/  FH_RSCSR_CHNL0_WPTR ; 
 int /*<<< orphan*/  FH_TSSR_TX_ERROR_REG ; 
 int /*<<< orphan*/  FH_TSSR_TX_STATUS_REG ; 
 int /*<<< orphan*/  IWL_CMD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *get_fh_string(int cmd)
{
	switch (cmd) {
	IWL_CMD(FH_RSCSR_CHNL0_STTS_WPTR_REG);
	IWL_CMD(FH_RSCSR_CHNL0_RBDCB_BASE_REG);
	IWL_CMD(FH_RSCSR_CHNL0_WPTR);
	IWL_CMD(FH_MEM_RCSR_CHNL0_CONFIG_REG);
	IWL_CMD(FH_MEM_RSSR_SHARED_CTRL_REG);
	IWL_CMD(FH_MEM_RSSR_RX_STATUS_REG);
	IWL_CMD(FH_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV);
	IWL_CMD(FH_TSSR_TX_STATUS_REG);
	IWL_CMD(FH_TSSR_TX_ERROR_REG);
	default:
		return "UNKNOWN";
	}
#undef IWL_CMD
}