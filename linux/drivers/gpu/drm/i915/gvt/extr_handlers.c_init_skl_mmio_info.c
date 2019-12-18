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
 int /*<<< orphan*/  BDW_SCRATCH1 ; 
 int /*<<< orphan*/  CDCLK_CTL ; 
 int /*<<< orphan*/  CHICKEN_PAR1_1 ; 
 int /*<<< orphan*/  CSFE_CHICKEN1_REG ; 
 int /*<<< orphan*/  CSR_HTP_SKL ; 
 int /*<<< orphan*/  CSR_LAST_WRITE ; 
 int /*<<< orphan*/  CSR_SSP_BASE ; 
 int /*<<< orphan*/  CUR_BUF_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUR_WM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUR_WM_TRANS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBUF_CTL ; 
 int /*<<< orphan*/  DC_STATE_DEBUG ; 
 int /*<<< orphan*/  DC_STATE_EN ; 
 int /*<<< orphan*/  DISPIO_CR_TX_BMU_CR0 ; 
 int /*<<< orphan*/  DMA_CTRL ; 
 int /*<<< orphan*/  DPLL_CTRL1 ; 
 int /*<<< orphan*/  DPLL_CTRL2 ; 
 int /*<<< orphan*/  DPLL_STATUS ; 
 int D_KBL ; 
 int D_SKL ; 
 int D_SKL_PLUS ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_BLITTER_GEN9 ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_MEDIA_GEN9 ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_RENDER_GEN9 ; 
 int /*<<< orphan*/  FORCEWAKE_BLITTER_GEN9 ; 
 int /*<<< orphan*/  FORCEWAKE_MEDIA_GEN9 ; 
 int /*<<< orphan*/  FORCEWAKE_RENDER_GEN9 ; 
 int F_CMD_ACCESS ; 
 int F_MODE_MASK ; 
 int /*<<< orphan*/  GAMT_CHKN_BIT_REG ; 
 int /*<<< orphan*/  GEN6_STOLEN_RESERVED ; 
 int /*<<< orphan*/  GEN7_FF_SLICE_CS_CHICKEN1 ; 
 int /*<<< orphan*/  GEN7_L3CNTLREG2 ; 
 int /*<<< orphan*/  GEN8_GARBCNTL ; 
 int /*<<< orphan*/  GEN8_HDC_CHICKEN1 ; 
 int /*<<< orphan*/  GEN9_CS_DEBUG_MODE1 ; 
 int /*<<< orphan*/  GEN9_CTX_PREEMPT_REG ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 int /*<<< orphan*/  GEN9_GFX_MOCS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN9_MEDIA_PG_IDLE_HYSTERESIS ; 
 int /*<<< orphan*/  GEN9_PG_ENABLE ; 
 int /*<<< orphan*/  GEN9_RENDER_PG_IDLE_HYSTERESIS ; 
 int /*<<< orphan*/  GEN9_WM_CHICKEN3 ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL1 ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL2 ; 
 int /*<<< orphan*/  LCPLL1_CTL ; 
 int /*<<< orphan*/  LCPLL2_CTL ; 
 int /*<<< orphan*/  MMCD_MISC_CTRL ; 
 int /*<<< orphan*/  MMIO_D (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMIO_DFH (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_DH (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_F (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_RING_DFH (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PIPE_B ; 
 int /*<<< orphan*/  PIPE_C ; 
 int /*<<< orphan*/  PLANE_BUF_CFG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLANE_NV12_BUF_CFG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLANE_WM (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE_WM_TRANS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RC6_LOCATION ; 
 int /*<<< orphan*/  RPM_CONFIG0 ; 
 int /*<<< orphan*/  SKL_DFSM ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRTTE ; 
 int /*<<< orphan*/  TRVADR ; 
 int /*<<< orphan*/  TRVATTL3PTRDW (int) ; 
 int _DPB_AUX_CH_CTL ; 
 int _DPC_AUX_CH_CTL ; 
 int _DPD_AUX_CH_CTL ; 
 int _DPLL1_CFGCR1 ; 
 int _DPLL1_CFGCR2 ; 
 int _DPLL2_CFGCR1 ; 
 int _DPLL2_CFGCR2 ; 
 int _DPLL3_CFGCR1 ; 
 int _DPLL3_CFGCR2 ; 
 int /*<<< orphan*/  _MMIO (int) ; 
 int _PLANE_CTL_3_A ; 
 int _PLANE_CTL_3_B ; 
 int _PLANE_KEYMAX_1 (int /*<<< orphan*/ ) ; 
 int _PLANE_KEYMSK_1 (int /*<<< orphan*/ ) ; 
 int _PLANE_KEYVAL_1 (int /*<<< orphan*/ ) ; 
 int _PLANE_SURF_3_A ; 
 int _REG_701C0 (int /*<<< orphan*/ ,int) ; 
 int _REG_701C4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csfe_chicken1_mmio_write ; 
 int /*<<< orphan*/ * dma_ctrl_write ; 
 int /*<<< orphan*/ * dp_aux_ch_ctl_mmio_write ; 
 int /*<<< orphan*/ * dpll_status_read ; 
 int /*<<< orphan*/ * gen9_dbuf_ctl_mmio_write ; 
 int /*<<< orphan*/ * gen9_trtt_chicken_write ; 
 int /*<<< orphan*/ * gen9_trtte_write ; 
 int /*<<< orphan*/ * mul_force_wake_write ; 
 int /*<<< orphan*/ * pf_write ; 
 int /*<<< orphan*/ * skl_lcpll_write ; 
 int /*<<< orphan*/ * skl_power_well_ctl_write ; 

__attribute__((used)) static int init_skl_mmio_info(struct intel_gvt *gvt)
{
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	int ret;

	MMIO_DH(FORCEWAKE_RENDER_GEN9, D_SKL_PLUS, NULL, mul_force_wake_write);
	MMIO_DH(FORCEWAKE_ACK_RENDER_GEN9, D_SKL_PLUS, NULL, NULL);
	MMIO_DH(FORCEWAKE_BLITTER_GEN9, D_SKL_PLUS, NULL, mul_force_wake_write);
	MMIO_DH(FORCEWAKE_ACK_BLITTER_GEN9, D_SKL_PLUS, NULL, NULL);
	MMIO_DH(FORCEWAKE_MEDIA_GEN9, D_SKL_PLUS, NULL, mul_force_wake_write);
	MMIO_DH(FORCEWAKE_ACK_MEDIA_GEN9, D_SKL_PLUS, NULL, NULL);

	MMIO_F(_MMIO(_DPB_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_SKL_PLUS, NULL,
						dp_aux_ch_ctl_mmio_write);
	MMIO_F(_MMIO(_DPC_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_SKL_PLUS, NULL,
						dp_aux_ch_ctl_mmio_write);
	MMIO_F(_MMIO(_DPD_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_SKL_PLUS, NULL,
						dp_aux_ch_ctl_mmio_write);

	MMIO_D(HSW_PWR_WELL_CTL1, D_SKL_PLUS);
	MMIO_DH(HSW_PWR_WELL_CTL2, D_SKL_PLUS, NULL, skl_power_well_ctl_write);

	MMIO_DH(DBUF_CTL, D_SKL_PLUS, NULL, gen9_dbuf_ctl_mmio_write);

	MMIO_D(GEN9_PG_ENABLE, D_SKL_PLUS);
	MMIO_D(GEN9_MEDIA_PG_IDLE_HYSTERESIS, D_SKL_PLUS);
	MMIO_D(GEN9_RENDER_PG_IDLE_HYSTERESIS, D_SKL_PLUS);
	MMIO_DFH(GEN9_GAMT_ECO_REG_RW_IA, D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DH(MMCD_MISC_CTRL, D_SKL_PLUS, NULL, NULL);
	MMIO_DH(CHICKEN_PAR1_1, D_SKL_PLUS, NULL, NULL);
	MMIO_D(DC_STATE_EN, D_SKL_PLUS);
	MMIO_D(DC_STATE_DEBUG, D_SKL_PLUS);
	MMIO_D(CDCLK_CTL, D_SKL_PLUS);
	MMIO_DH(LCPLL1_CTL, D_SKL_PLUS, NULL, skl_lcpll_write);
	MMIO_DH(LCPLL2_CTL, D_SKL_PLUS, NULL, skl_lcpll_write);
	MMIO_D(_MMIO(_DPLL1_CFGCR1), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL2_CFGCR1), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL3_CFGCR1), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL1_CFGCR2), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL2_CFGCR2), D_SKL_PLUS);
	MMIO_D(_MMIO(_DPLL3_CFGCR2), D_SKL_PLUS);
	MMIO_D(DPLL_CTRL1, D_SKL_PLUS);
	MMIO_D(DPLL_CTRL2, D_SKL_PLUS);
	MMIO_DH(DPLL_STATUS, D_SKL_PLUS, dpll_status_read, NULL);

	MMIO_DH(SKL_PS_WIN_POS(PIPE_A, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_A, 1), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_B, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_B, 1), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_C, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_POS(PIPE_C, 1), D_SKL_PLUS, NULL, pf_write);

	MMIO_DH(SKL_PS_WIN_SZ(PIPE_A, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_A, 1), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_B, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_B, 1), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_C, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_WIN_SZ(PIPE_C, 1), D_SKL_PLUS, NULL, pf_write);

	MMIO_DH(SKL_PS_CTRL(PIPE_A, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_CTRL(PIPE_A, 1), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_CTRL(PIPE_B, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_CTRL(PIPE_B, 1), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_CTRL(PIPE_C, 0), D_SKL_PLUS, NULL, pf_write);
	MMIO_DH(SKL_PS_CTRL(PIPE_C, 1), D_SKL_PLUS, NULL, pf_write);

	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 2), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_A, 3), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 2), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_B, 3), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 2), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_BUF_CFG(PIPE_C, 3), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(CUR_BUF_CFG(PIPE_A), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(CUR_BUF_CFG(PIPE_B), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(CUR_BUF_CFG(PIPE_C), D_SKL_PLUS, NULL, NULL);

	MMIO_F(PLANE_WM(PIPE_A, 0, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(PLANE_WM(PIPE_A, 1, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(PLANE_WM(PIPE_A, 2, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);

	MMIO_F(PLANE_WM(PIPE_B, 0, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(PLANE_WM(PIPE_B, 1, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(PLANE_WM(PIPE_B, 2, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);

	MMIO_F(PLANE_WM(PIPE_C, 0, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(PLANE_WM(PIPE_C, 1, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(PLANE_WM(PIPE_C, 2, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);

	MMIO_F(CUR_WM(PIPE_A, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(CUR_WM(PIPE_B, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);
	MMIO_F(CUR_WM(PIPE_C, 0), 4 * 8, 0, 0, 0, D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_WM_TRANS(PIPE_A, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_WM_TRANS(PIPE_A, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_WM_TRANS(PIPE_A, 2), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_WM_TRANS(PIPE_B, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_WM_TRANS(PIPE_B, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_WM_TRANS(PIPE_B, 2), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_WM_TRANS(PIPE_C, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_WM_TRANS(PIPE_C, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_WM_TRANS(PIPE_C, 2), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(CUR_WM_TRANS(PIPE_A), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(CUR_WM_TRANS(PIPE_B), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(CUR_WM_TRANS(PIPE_C), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 2), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_A, 3), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 2), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_B, 3), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 0), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 1), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 2), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(PLANE_NV12_BUF_CFG(PIPE_C, 3), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 1)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 2)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 3)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_A, 4)), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 1)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 2)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 3)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_B, 4)), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 1)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 2)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 3)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C0(PIPE_C, 4)), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 1)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 2)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 3)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_A, 4)), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 1)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 2)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 3)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_B, 4)), D_SKL_PLUS, NULL, NULL);

	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 1)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 2)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 3)), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(_REG_701C4(PIPE_C, 4)), D_SKL_PLUS, NULL, NULL);

	MMIO_D(_MMIO(_PLANE_CTL_3_A), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_CTL_3_B), D_SKL_PLUS);
	MMIO_D(_MMIO(0x72380), D_SKL_PLUS);
	MMIO_D(_MMIO(0x7239c), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_SURF_3_A), D_SKL_PLUS);

	MMIO_D(CSR_SSP_BASE, D_SKL_PLUS);
	MMIO_D(CSR_HTP_SKL, D_SKL_PLUS);
	MMIO_D(CSR_LAST_WRITE, D_SKL_PLUS);

	MMIO_DFH(BDW_SCRATCH1, D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);

	MMIO_D(SKL_DFSM, D_SKL_PLUS);
	MMIO_D(DISPIO_CR_TX_BMU_CR0, D_SKL_PLUS);

	MMIO_F(GEN9_GFX_MOCS(0), 0x7f8, F_CMD_ACCESS, 0, 0, D_SKL_PLUS,
		NULL, NULL);
	MMIO_F(GEN7_L3CNTLREG2, 0x80, F_CMD_ACCESS, 0, 0, D_SKL_PLUS,
		NULL, NULL);

	MMIO_D(RPM_CONFIG0, D_SKL_PLUS);
	MMIO_D(_MMIO(0xd08), D_SKL_PLUS);
	MMIO_D(RC6_LOCATION, D_SKL_PLUS);
	MMIO_DFH(GEN7_FF_SLICE_CS_CHICKEN1, D_SKL_PLUS,
		 F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(GEN9_CS_DEBUG_MODE1, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		NULL, NULL);

	/* TRTT */
	MMIO_DFH(TRVATTL3PTRDW(0), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(TRVATTL3PTRDW(1), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(TRVATTL3PTRDW(2), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(TRVATTL3PTRDW(3), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(TRVADR, D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(TRTTE, D_SKL_PLUS, F_CMD_ACCESS,
		NULL, gen9_trtte_write);
	MMIO_DH(_MMIO(0x4dfc), D_SKL_PLUS, NULL, gen9_trtt_chicken_write);

	MMIO_D(_MMIO(0x46430), D_SKL_PLUS);

	MMIO_D(_MMIO(0x46520), D_SKL_PLUS);

	MMIO_D(_MMIO(0xc403c), D_SKL_PLUS);
	MMIO_DFH(GEN8_GARBCNTL, D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DH(DMA_CTRL, D_SKL_PLUS, NULL, dma_ctrl_write);

	MMIO_D(_MMIO(0x65900), D_SKL_PLUS);
	MMIO_D(GEN6_STOLEN_RESERVED, D_SKL_PLUS);
	MMIO_D(_MMIO(0x4068), D_SKL_PLUS);
	MMIO_D(_MMIO(0x67054), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6e560), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6e554), D_SKL_PLUS);
	MMIO_D(_MMIO(0x2b20), D_SKL_PLUS);
	MMIO_D(_MMIO(0x65f00), D_SKL_PLUS);
	MMIO_D(_MMIO(0x65f08), D_SKL_PLUS);
	MMIO_D(_MMIO(0x320f0), D_SKL_PLUS);

	MMIO_D(_MMIO(0x70034), D_SKL_PLUS);
	MMIO_D(_MMIO(0x71034), D_SKL_PLUS);
	MMIO_D(_MMIO(0x72034), D_SKL_PLUS);

	MMIO_D(_MMIO(_PLANE_KEYVAL_1(PIPE_A)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYVAL_1(PIPE_B)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYVAL_1(PIPE_C)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMAX_1(PIPE_A)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMAX_1(PIPE_B)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMAX_1(PIPE_C)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMSK_1(PIPE_A)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMSK_1(PIPE_B)), D_SKL_PLUS);
	MMIO_D(_MMIO(_PLANE_KEYMSK_1(PIPE_C)), D_SKL_PLUS);

	MMIO_D(_MMIO(0x44500), D_SKL_PLUS);
#define CSFE_CHICKEN1_REG(base) _MMIO((base) + 0xD4)
	MMIO_RING_DFH(CSFE_CHICKEN1_REG, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		      NULL, csfe_chicken1_mmio_write);
#undef CSFE_CHICKEN1_REG
	MMIO_DFH(GEN8_HDC_CHICKEN1, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		 NULL, NULL);
	MMIO_DFH(GEN9_WM_CHICKEN3, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		 NULL, NULL);

	MMIO_D(GAMT_CHKN_BIT_REG, D_KBL);
	MMIO_D(GEN9_CTX_PREEMPT_REG, D_KBL | D_SKL);

	return 0;
}