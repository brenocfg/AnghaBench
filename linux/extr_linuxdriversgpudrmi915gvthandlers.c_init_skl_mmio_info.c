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
 int /*<<< orphan*/  CUR_BUF_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUR_WM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUR_WM_TRANS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBUF_CTL ; 
 int /*<<< orphan*/  DMA_CTRL ; 
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
 int /*<<< orphan*/  GEN8_HDC_CHICKEN1 ; 
 int /*<<< orphan*/  GEN9_CSFE_CHICKEN1_RCS ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 int /*<<< orphan*/  GEN9_MEDIA_PG_IDLE_HYSTERESIS ; 
 int /*<<< orphan*/  GEN9_RENDER_PG_IDLE_HYSTERESIS ; 
 int /*<<< orphan*/  GEN9_WM_CHICKEN3 ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_BIOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DRIVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_D (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMIO_DFH (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_DH (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_F (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PIPE_B ; 
 int /*<<< orphan*/  PIPE_C ; 
 int /*<<< orphan*/  PLANE_BUF_CFG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLANE_NV12_BUF_CFG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLANE_WM (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE_WM_TRANS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RC6_LOCATION ; 
 int /*<<< orphan*/  RPM_CONFIG0 ; 
 int /*<<< orphan*/  SKL_DISP_PW_MISC_IO ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int /*<<< orphan*/ ,int) ; 
 int _DPB_AUX_CH_CTL ; 
 int _DPC_AUX_CH_CTL ; 
 int _DPD_AUX_CH_CTL ; 
 int /*<<< orphan*/  _MMIO (int) ; 
 int _PLANE_KEYMAX_1 (int /*<<< orphan*/ ) ; 
 int _PLANE_KEYMSK_1 (int /*<<< orphan*/ ) ; 
 int _PLANE_KEYVAL_1 (int /*<<< orphan*/ ) ; 
 int _REG_701C0 (int /*<<< orphan*/ ,int) ; 
 int _REG_701C4 (int /*<<< orphan*/ ,int) ; 
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

	/*
	 * Use an arbitrary power well controlled by the PWR_WELL_CTL
	 * register.
	 */
	MMIO_D(HSW_PWR_WELL_CTL_BIOS(SKL_DISP_PW_MISC_IO), D_SKL_PLUS);
	MMIO_DH(HSW_PWR_WELL_CTL_DRIVER(SKL_DISP_PW_MISC_IO), D_SKL_PLUS, NULL,
		skl_power_well_ctl_write);

	MMIO_DH(DBUF_CTL, D_SKL_PLUS, NULL, gen9_dbuf_ctl_mmio_write);

	MMIO_D(_MMIO(0xa210), D_SKL_PLUS);
	MMIO_D(GEN9_MEDIA_PG_IDLE_HYSTERESIS, D_SKL_PLUS);
	MMIO_D(GEN9_RENDER_PG_IDLE_HYSTERESIS, D_SKL_PLUS);
	MMIO_DFH(GEN9_GAMT_ECO_REG_RW_IA, D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DH(_MMIO(0x4ddc), D_SKL_PLUS, NULL, NULL);
	MMIO_DH(_MMIO(0x42080), D_SKL_PLUS, NULL, NULL);
	MMIO_D(_MMIO(0x45504), D_SKL_PLUS);
	MMIO_D(_MMIO(0x45520), D_SKL_PLUS);
	MMIO_D(_MMIO(0x46000), D_SKL_PLUS);
	MMIO_DH(_MMIO(0x46010), D_SKL_PLUS, NULL, skl_lcpll_write);
	MMIO_DH(_MMIO(0x46014), D_SKL_PLUS, NULL, skl_lcpll_write);
	MMIO_D(_MMIO(0x6C040), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6C048), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6C050), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6C044), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6C04C), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6C054), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6c058), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6c05c), D_SKL_PLUS);
	MMIO_DH(_MMIO(0x6c060), D_SKL_PLUS, dpll_status_read, NULL);

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

	MMIO_D(_MMIO(0x70380), D_SKL_PLUS);
	MMIO_D(_MMIO(0x71380), D_SKL_PLUS);
	MMIO_D(_MMIO(0x72380), D_SKL_PLUS);
	MMIO_D(_MMIO(0x7239c), D_SKL_PLUS);
	MMIO_D(_MMIO(0x7039c), D_SKL_PLUS);

	MMIO_D(_MMIO(0x8f074), D_SKL_PLUS);
	MMIO_D(_MMIO(0x8f004), D_SKL_PLUS);
	MMIO_D(_MMIO(0x8f034), D_SKL_PLUS);

	MMIO_D(_MMIO(0xb11c), D_SKL_PLUS);

	MMIO_D(_MMIO(0x51000), D_SKL_PLUS);
	MMIO_D(_MMIO(0x6c00c), D_SKL_PLUS);

	MMIO_F(_MMIO(0xc800), 0x7f8, F_CMD_ACCESS, 0, 0, D_SKL_PLUS,
		NULL, NULL);
	MMIO_F(_MMIO(0xb020), 0x80, F_CMD_ACCESS, 0, 0, D_SKL_PLUS,
		NULL, NULL);

	MMIO_D(RPM_CONFIG0, D_SKL_PLUS);
	MMIO_D(_MMIO(0xd08), D_SKL_PLUS);
	MMIO_D(RC6_LOCATION, D_SKL_PLUS);
	MMIO_DFH(_MMIO(0x20e0), D_SKL_PLUS, F_MODE_MASK, NULL, NULL);
	MMIO_DFH(_MMIO(0x20ec), D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		NULL, NULL);

	/* TRTT */
	MMIO_DFH(_MMIO(0x4de0), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x4de4), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x4de8), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x4dec), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x4df0), D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x4df4), D_SKL_PLUS, F_CMD_ACCESS,
		NULL, gen9_trtte_write);
	MMIO_DH(_MMIO(0x4dfc), D_SKL_PLUS, NULL, gen9_trtt_chicken_write);

	MMIO_D(_MMIO(0x46430), D_SKL_PLUS);

	MMIO_D(_MMIO(0x46520), D_SKL_PLUS);

	MMIO_D(_MMIO(0xc403c), D_SKL_PLUS);
	MMIO_D(_MMIO(0xb004), D_SKL_PLUS);
	MMIO_DH(DMA_CTRL, D_SKL_PLUS, NULL, dma_ctrl_write);

	MMIO_D(_MMIO(0x65900), D_SKL_PLUS);
	MMIO_D(_MMIO(0x1082c0), D_SKL_PLUS);
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
	MMIO_DFH(GEN9_CSFE_CHICKEN1_RCS, D_SKL_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(GEN8_HDC_CHICKEN1, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		 NULL, NULL);
	MMIO_DFH(GEN9_WM_CHICKEN3, D_SKL_PLUS, F_MODE_MASK | F_CMD_ACCESS,
		 NULL, NULL);

	MMIO_D(_MMIO(0x4ab8), D_KBL);
	MMIO_D(_MMIO(0x2248), D_KBL | D_SKL);

	return 0;
}