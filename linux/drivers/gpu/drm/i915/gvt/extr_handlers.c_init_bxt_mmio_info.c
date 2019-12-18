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
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_DE_PLL_CTL ; 
 int /*<<< orphan*/  BXT_DE_PLL_ENABLE ; 
 int /*<<< orphan*/  BXT_DSI_PLL_CTL ; 
 int /*<<< orphan*/  BXT_DSI_PLL_ENABLE ; 
 int /*<<< orphan*/  BXT_PHY_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PHY_CTL_FAMILY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW28 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW30 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW9 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_CL2CM_DW6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PCS_DW10_GRP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PCS_DW10_LN01 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PCS_DW12_GRP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PCS_DW12_LN01 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PCS_DW12_LN23 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PLL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BXT_PORT_PLL_EBB_0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PLL_EBB_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_PLL_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_REF_DW3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_REF_DW6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_REF_DW8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW14_LN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW2_GRP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW2_LN0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW3_GRP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW3_LN0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW4_GRP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_PORT_TX_DW4_LN0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXT_P_CR_GT_DISP_PWRON ; 
 int /*<<< orphan*/  BXT_RP_STATE_CAP ; 
 int /*<<< orphan*/  DONE_REG ; 
 int /*<<< orphan*/  DPIO_CH0 ; 
 int /*<<< orphan*/  DPIO_CH1 ; 
 int /*<<< orphan*/  DPIO_PHY0 ; 
 int /*<<< orphan*/  DPIO_PHY1 ; 
 int /*<<< orphan*/  D_BXT ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  ERROR_GEN6 ; 
 int /*<<< orphan*/  F_CMD_ACCESS ; 
 int /*<<< orphan*/  GEN6_GFXPAUSE ; 
 int /*<<< orphan*/  GEN7_ROW_INSTDONE ; 
 int /*<<< orphan*/  GEN7_SAMPLER_INSTDONE ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA0 ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA1 ; 
 int /*<<< orphan*/  GEN8_L3SQCREG1 ; 
 int /*<<< orphan*/  GEN8_PUSHBUS_CONTROL ; 
 int /*<<< orphan*/  GEN8_PUSHBUS_ENABLE ; 
 int /*<<< orphan*/  GEN8_PUSHBUS_SHIFT ; 
 int /*<<< orphan*/  GEN9_CLKGATE_DIS_0 ; 
 int /*<<< orphan*/  GEN9_CLKGATE_DIS_4 ; 
 int /*<<< orphan*/  GEN9_CTX_PREEMPT_REG ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_GCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_DFH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_DH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_F (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_RING_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGTBL_ER ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  RC6_CTX_BASE ; 
 int /*<<< orphan*/  RING_BBADDR_UDW ; 
 int /*<<< orphan*/  RING_BBSTATE ; 
 int /*<<< orphan*/  RING_DMA_FADD ; 
 int /*<<< orphan*/  RING_DMA_FADD_UDW ; 
 int /*<<< orphan*/  RING_INSTPS ; 
 int /*<<< orphan*/  RING_IPEHR ; 
 int /*<<< orphan*/  RING_IPEIR ; 
 int /*<<< orphan*/  RING_PSMI_CTL ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSCODER_A ; 
 int /*<<< orphan*/  TRANSCODER_B ; 
 int /*<<< orphan*/  TRANSCODER_C ; 
 int /*<<< orphan*/  _MMIO (int) ; 
 int /*<<< orphan*/ * bxt_de_pll_enable_write ; 
 int /*<<< orphan*/ * bxt_gt_disp_pwron_write ; 
 int /*<<< orphan*/ * bxt_pcs_dw12_grp_write ; 
 int /*<<< orphan*/ * bxt_phy_ctl_family_write ; 
 int /*<<< orphan*/ * bxt_port_pll_enable_write ; 
 int /*<<< orphan*/ * bxt_port_tx_dw3_read ; 

__attribute__((used)) static int init_bxt_mmio_info(struct intel_gvt *gvt)
{
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	int ret;

	MMIO_F(_MMIO(0x80000), 0x3000, 0, 0, 0, D_BXT, NULL, NULL);

	MMIO_D(GEN7_SAMPLER_INSTDONE, D_BXT);
	MMIO_D(GEN7_ROW_INSTDONE, D_BXT);
	MMIO_D(GEN8_FAULT_TLB_DATA0, D_BXT);
	MMIO_D(GEN8_FAULT_TLB_DATA1, D_BXT);
	MMIO_D(ERROR_GEN6, D_BXT);
	MMIO_D(DONE_REG, D_BXT);
	MMIO_D(EIR, D_BXT);
	MMIO_D(PGTBL_ER, D_BXT);
	MMIO_D(_MMIO(0x4194), D_BXT);
	MMIO_D(_MMIO(0x4294), D_BXT);
	MMIO_D(_MMIO(0x4494), D_BXT);

	MMIO_RING_D(RING_PSMI_CTL, D_BXT);
	MMIO_RING_D(RING_DMA_FADD, D_BXT);
	MMIO_RING_D(RING_DMA_FADD_UDW, D_BXT);
	MMIO_RING_D(RING_IPEHR, D_BXT);
	MMIO_RING_D(RING_INSTPS, D_BXT);
	MMIO_RING_D(RING_BBADDR_UDW, D_BXT);
	MMIO_RING_D(RING_BBSTATE, D_BXT);
	MMIO_RING_D(RING_IPEIR, D_BXT);

	MMIO_F(SOFT_SCRATCH(0), 16 * 4, 0, 0, 0, D_BXT, NULL, NULL);

	MMIO_DH(BXT_P_CR_GT_DISP_PWRON, D_BXT, NULL, bxt_gt_disp_pwron_write);
	MMIO_D(BXT_RP_STATE_CAP, D_BXT);
	MMIO_DH(BXT_PHY_CTL_FAMILY(DPIO_PHY0), D_BXT,
		NULL, bxt_phy_ctl_family_write);
	MMIO_DH(BXT_PHY_CTL_FAMILY(DPIO_PHY1), D_BXT,
		NULL, bxt_phy_ctl_family_write);
	MMIO_D(BXT_PHY_CTL(PORT_A), D_BXT);
	MMIO_D(BXT_PHY_CTL(PORT_B), D_BXT);
	MMIO_D(BXT_PHY_CTL(PORT_C), D_BXT);
	MMIO_DH(BXT_PORT_PLL_ENABLE(PORT_A), D_BXT,
		NULL, bxt_port_pll_enable_write);
	MMIO_DH(BXT_PORT_PLL_ENABLE(PORT_B), D_BXT,
		NULL, bxt_port_pll_enable_write);
	MMIO_DH(BXT_PORT_PLL_ENABLE(PORT_C), D_BXT, NULL,
		bxt_port_pll_enable_write);

	MMIO_D(BXT_PORT_CL1CM_DW0(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW9(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW10(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW28(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW30(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_CL2CM_DW6(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_REF_DW3(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_REF_DW6(DPIO_PHY0), D_BXT);
	MMIO_D(BXT_PORT_REF_DW8(DPIO_PHY0), D_BXT);

	MMIO_D(BXT_PORT_CL1CM_DW0(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW9(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW10(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW28(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL1CM_DW30(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_CL2CM_DW6(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_REF_DW3(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_REF_DW6(DPIO_PHY1), D_BXT);
	MMIO_D(BXT_PORT_REF_DW8(DPIO_PHY1), D_BXT);

	MMIO_D(BXT_PORT_PLL_EBB_0(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PLL_EBB_4(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_LN01(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN01(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN23(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_PCS_DW12_GRP(DPIO_PHY0, DPIO_CH0), D_BXT,
		NULL, bxt_pcs_dw12_grp_write);
	MMIO_D(BXT_PORT_TX_DW2_LN0(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW2_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_TX_DW3_LN0(DPIO_PHY0, DPIO_CH0), D_BXT,
		bxt_port_tx_dw3_read, NULL);
	MMIO_D(BXT_PORT_TX_DW3_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_LN0(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_GRP(DPIO_PHY0, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 6), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 8), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 9), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH0, 10), D_BXT);

	MMIO_D(BXT_PORT_PLL_EBB_0(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PLL_EBB_4(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_LN01(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN01(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN23(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_DH(BXT_PORT_PCS_DW12_GRP(DPIO_PHY0, DPIO_CH1), D_BXT,
		NULL, bxt_pcs_dw12_grp_write);
	MMIO_D(BXT_PORT_TX_DW2_LN0(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW2_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_DH(BXT_PORT_TX_DW3_LN0(DPIO_PHY0, DPIO_CH1), D_BXT,
		bxt_port_tx_dw3_read, NULL);
	MMIO_D(BXT_PORT_TX_DW3_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_LN0(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_GRP(DPIO_PHY0, DPIO_CH1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 2), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY0, DPIO_CH1, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 0), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 1), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 2), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 6), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 8), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 9), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY0, DPIO_CH1, 10), D_BXT);

	MMIO_D(BXT_PORT_PLL_EBB_0(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PLL_EBB_4(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_LN01(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW10_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN01(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_PCS_DW12_LN23(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_PCS_DW12_GRP(DPIO_PHY1, DPIO_CH0), D_BXT,
		NULL, bxt_pcs_dw12_grp_write);
	MMIO_D(BXT_PORT_TX_DW2_LN0(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW2_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_DH(BXT_PORT_TX_DW3_LN0(DPIO_PHY1, DPIO_CH0), D_BXT,
		bxt_port_tx_dw3_read, NULL);
	MMIO_D(BXT_PORT_TX_DW3_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_LN0(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW4_GRP(DPIO_PHY1, DPIO_CH0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_TX_DW14_LN(DPIO_PHY1, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 0), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 1), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 2), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 3), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 6), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 8), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 9), D_BXT);
	MMIO_D(BXT_PORT_PLL(DPIO_PHY1, DPIO_CH0, 10), D_BXT);

	MMIO_D(BXT_DE_PLL_CTL, D_BXT);
	MMIO_DH(BXT_DE_PLL_ENABLE, D_BXT, NULL, bxt_de_pll_enable_write);
	MMIO_D(BXT_DSI_PLL_CTL, D_BXT);
	MMIO_D(BXT_DSI_PLL_ENABLE, D_BXT);

	MMIO_D(GEN9_CLKGATE_DIS_0, D_BXT);
	MMIO_D(GEN9_CLKGATE_DIS_4, D_BXT);

	MMIO_D(HSW_TVIDEO_DIP_GCP(TRANSCODER_A), D_BXT);
	MMIO_D(HSW_TVIDEO_DIP_GCP(TRANSCODER_B), D_BXT);
	MMIO_D(HSW_TVIDEO_DIP_GCP(TRANSCODER_C), D_BXT);

	MMIO_D(RC6_CTX_BASE, D_BXT);

	MMIO_D(GEN8_PUSHBUS_CONTROL, D_BXT);
	MMIO_D(GEN8_PUSHBUS_ENABLE, D_BXT);
	MMIO_D(GEN8_PUSHBUS_SHIFT, D_BXT);
	MMIO_D(GEN6_GFXPAUSE, D_BXT);
	MMIO_DFH(GEN8_L3SQCREG1, D_BXT, F_CMD_ACCESS, NULL, NULL);

	MMIO_DFH(GEN9_CTX_PREEMPT_REG, D_BXT, F_CMD_ACCESS, NULL, NULL);

	return 0;
}