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
 int /*<<< orphan*/  ARB_MODE ; 
 int /*<<< orphan*/  BCLRPAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCS_SWCTRL ; 
 int /*<<< orphan*/  BLC_PWM_CPU_CTL ; 
 int /*<<< orphan*/  BLC_PWM_CPU_CTL2 ; 
 int /*<<< orphan*/  BLC_PWM_PCH_CTL1 ; 
 int /*<<< orphan*/  BLC_PWM_PCH_CTL2 ; 
 int /*<<< orphan*/  BLT_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  BSD_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int /*<<< orphan*/  CACHE_MODE_0_GEN7 ; 
 int /*<<< orphan*/  CACHE_MODE_1 ; 
 int /*<<< orphan*/  CCID ; 
 int /*<<< orphan*/  CL_INVOCATION_COUNT ; 
 int /*<<< orphan*/  CL_PRIMITIVES_COUNT ; 
 int /*<<< orphan*/  COMMON_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  CPU_VGACNTRL ; 
 int /*<<< orphan*/  CURBASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURCNTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUR_FBC_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDI_BUF_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DERRMR ; 
 int /*<<< orphan*/  DIGITAL_PORT_HOTPLUG_CNTRL ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int /*<<< orphan*/  DISP_ARB_CTL2 ; 
 int /*<<< orphan*/  DP_TP_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_TP_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPCNTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPOFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPSTRIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPSURF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPSURFLIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS_INVOCATION_COUNT ; 
 int /*<<< orphan*/  D_ALL ; 
 int /*<<< orphan*/  D_BDW ; 
 int /*<<< orphan*/  D_BDW_PLUS ; 
 int /*<<< orphan*/  D_PRE_SKL ; 
 int /*<<< orphan*/  ECOBUS ; 
 int /*<<< orphan*/  ECOSKPD ; 
 int /*<<< orphan*/  FDI_RX_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDI_RX_IIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDI_RX_IMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FENCE_REG_GEN6_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCEWAKE ; 
 int /*<<< orphan*/  FORCEWAKE_ACK ; 
 int /*<<< orphan*/  FORCEWAKE_ACK_HSW ; 
 int /*<<< orphan*/  FORCEWAKE_MT ; 
 int /*<<< orphan*/  FPGA_DBG ; 
 int /*<<< orphan*/  FUSE_STRAP ; 
 int F_CMD_ACCESS ; 
 int F_MODE_MASK ; 
 int F_UNALIGN ; 
 int /*<<< orphan*/  GAB_CTL ; 
 int /*<<< orphan*/  GAC_ECO_BITS ; 
 int /*<<< orphan*/  GAMMA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GAM_ECOCHK ; 
 int /*<<< orphan*/  GEN6_BLITTER_ECOSKPD ; 
 int /*<<< orphan*/  GEN6_GDRST ; 
 int /*<<< orphan*/  GEN6_GT_CORE_STATUS ; 
 int /*<<< orphan*/  GEN6_GT_THREAD_STATUS_REG ; 
 int /*<<< orphan*/  GEN6_MBCTL ; 
 int /*<<< orphan*/  GEN6_PCODE_DATA ; 
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  GEN6_RC1_WAKE_RATE_LIMIT ; 
 int /*<<< orphan*/  GEN6_RC1e_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RC6_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RC6_WAKE_RATE_LIMIT ; 
 int /*<<< orphan*/  GEN6_RC6p_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RC6pp_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RC6pp_WAKE_RATE_LIMIT ; 
 int /*<<< orphan*/  GEN6_RC_CONTROL ; 
 int /*<<< orphan*/  GEN6_RC_EVALUATION_INTERVAL ; 
 int /*<<< orphan*/  GEN6_RC_IDLE_HYSTERSIS ; 
 int /*<<< orphan*/  GEN6_RC_SLEEP ; 
 int /*<<< orphan*/  GEN6_RC_STATE ; 
 int /*<<< orphan*/  GEN6_RC_VIDEO_FREQ ; 
 int /*<<< orphan*/  GEN6_RPNSWREQ ; 
 int /*<<< orphan*/  GEN6_RPSTAT1 ; 
 int /*<<< orphan*/  GEN6_RP_CONTROL ; 
 int /*<<< orphan*/  GEN6_RP_CUR_DOWN ; 
 int /*<<< orphan*/  GEN6_RP_CUR_DOWN_EI ; 
 int /*<<< orphan*/  GEN6_RP_CUR_UP ; 
 int /*<<< orphan*/  GEN6_RP_CUR_UP_EI ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_EI ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_TIMEOUT ; 
 int /*<<< orphan*/  GEN6_RP_IDLE_HYSTERSIS ; 
 int /*<<< orphan*/  GEN6_RP_INTERRUPT_LIMITS ; 
 int /*<<< orphan*/  GEN6_RP_PREV_DOWN ; 
 int /*<<< orphan*/  GEN6_RP_PREV_UP ; 
 int /*<<< orphan*/  GEN6_RP_UP_EI ; 
 int /*<<< orphan*/  GEN6_RP_UP_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_UCGCTL1 ; 
 int /*<<< orphan*/  GEN6_UCGCTL2 ; 
 int /*<<< orphan*/  GEN7_COMMON_SLICE_CHICKEN1 ; 
 int /*<<< orphan*/  GEN7_CXT_SIZE ; 
 int /*<<< orphan*/  GEN7_ERR_INT ; 
 int /*<<< orphan*/  GEN7_GT_MODE ; 
 int /*<<< orphan*/  GEN7_HALF_SLICE_CHICKEN1 ; 
 int /*<<< orphan*/  GEN7_SC_INSTDONE ; 
 int /*<<< orphan*/  GEN7_UCGCTL4 ; 
 int /*<<< orphan*/  GEN8_GAMW_ECO_DEV_RW_IA ; 
 int /*<<< orphan*/  GFX_FLSH_CNTL_GEN6 ; 
 int /*<<< orphan*/  GS_INVOCATION_COUNT ; 
 int /*<<< orphan*/  GS_PRIMITIVES_COUNT ; 
 int /*<<< orphan*/  GTFIFOCTL ; 
 int /*<<< orphan*/  GTFIFODBG ; 
 int /*<<< orphan*/  HALF_SLICE_CHICKEN3 ; 
 int /*<<< orphan*/  HBLANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_AUD_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_AUD_MISC_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_AUD_PIN_ELD_CP_VLD ; 
 int /*<<< orphan*/  HSW_DISP_PW_GLOBAL ; 
 int /*<<< orphan*/  HSW_EDRAM_CAP ; 
 int /*<<< orphan*/  HSW_IDICR ; 
 int /*<<< orphan*/  HSW_NDE_RSTWRN_OPT ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL5 ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL6 ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_BIOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DRIVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_KVMR ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HS_INVOCATION_COUNT ; 
 int /*<<< orphan*/  HTOTAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IA_PRIMITIVES_COUNT ; 
 int /*<<< orphan*/  IA_VERTICES_COUNT ; 
 int /*<<< orphan*/  ILK_DISPLAY_CHICKEN1 ; 
 int /*<<< orphan*/  ILK_DISPLAY_CHICKEN2 ; 
 int /*<<< orphan*/  ILK_DPFC_CB_BASE ; 
 int /*<<< orphan*/  ILK_DPFC_CHICKEN ; 
 int /*<<< orphan*/  ILK_DPFC_CONTROL ; 
 int /*<<< orphan*/  ILK_DPFC_FENCE_YOFF ; 
 int /*<<< orphan*/  ILK_DPFC_RECOMP_CTL ; 
 int /*<<< orphan*/  ILK_DPFC_STATUS ; 
 int /*<<< orphan*/  ILK_DSPCLK_GATE_D ; 
 int /*<<< orphan*/  ILK_FBC_RT_BASE ; 
 int /*<<< orphan*/  IPS_CTL ; 
 int /*<<< orphan*/  LCPLL_CTL ; 
 int /*<<< orphan*/  MMIO_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_DFH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_DH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_F (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_GM_RDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_RING_DFH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_RING_GM_RDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_RO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCH_ADPA ; 
 int /*<<< orphan*/  PCH_DPLL_SEL ; 
 int /*<<< orphan*/  PCH_DREF_CONTROL ; 
 int /*<<< orphan*/  PCH_GMBUS0 ; 
 int /*<<< orphan*/  PCH_GMBUS4 ; 
 int /*<<< orphan*/  PCH_GMBUS5 ; 
 int /*<<< orphan*/  PCH_GPIOA ; 
 int /*<<< orphan*/  PCH_LVDS ; 
 int /*<<< orphan*/  PCH_PORT_HOTPLUG ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_DIVISOR ; 
 int /*<<< orphan*/  PCH_PP_OFF_DELAYS ; 
 int /*<<< orphan*/  PCH_PP_ON_DELAYS ; 
 int /*<<< orphan*/  PCH_PP_STATUS ; 
 int /*<<< orphan*/  PCH_RAWCLK_FREQ ; 
 int /*<<< orphan*/  PF_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_HSCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_VSCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_WIN_POS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_WIN_SZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPECONF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPEDSL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPESRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPESTAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PIPE_B ; 
 int /*<<< orphan*/  PIPE_C ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_BY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RU_GU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RV_GV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_COEFF_RY_GY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_POSTOFF_ME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CSC_PREOFF_ME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_DATA_M1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_DATA_M2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_DATA_N1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_DATA_N2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_FLIPCOUNT_G4X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_FRMCOUNT_G4X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_LINK_M1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_LINK_M2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_LINK_N1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_LINK_N2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_MULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_WM_LINETIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIXCLK_GATE ; 
 int PORTA_HOTPLUG_STATUS_MASK ; 
 int PORTB_HOTPLUG_STATUS_MASK ; 
 int PORTC_HOTPLUG_STATUS_MASK ; 
 int PORTD_HOTPLUG_STATUS_MASK ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_D ; 
 int /*<<< orphan*/  PORT_E ; 
 int /*<<< orphan*/  PREC_PAL_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREC_PAL_GC_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREC_PAL_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_DEPTH_COUNT ; 
 int /*<<< orphan*/  PS_INVOCATION_COUNT ; 
 int /*<<< orphan*/  RING_ACTHD ; 
 int /*<<< orphan*/  RING_BBADDR ; 
 int /*<<< orphan*/  RING_CTL ; 
 int /*<<< orphan*/  RING_HEAD ; 
 int /*<<< orphan*/  RING_HWSTAM ; 
 int /*<<< orphan*/  RING_IMR ; 
 int /*<<< orphan*/  RING_INSTPM ; 
 int /*<<< orphan*/  RING_MI_MODE ; 
 int /*<<< orphan*/  RING_REG ; 
 int /*<<< orphan*/  RING_START ; 
 int /*<<< orphan*/  RING_SYNC_0 ; 
 int /*<<< orphan*/  RING_SYNC_1 ; 
 int /*<<< orphan*/  RING_TAIL ; 
 int /*<<< orphan*/  RING_TIMESTAMP ; 
 int /*<<< orphan*/  RING_TIMESTAMP_UDW ; 
 int /*<<< orphan*/  RSTDBYCTL ; 
 int /*<<< orphan*/  SBI_ADDR ; 
 int /*<<< orphan*/  SBI_CTL_STAT ; 
 int /*<<< orphan*/  SBI_DATA ; 
 int /*<<< orphan*/  SDEIER ; 
 int /*<<< orphan*/  SDEIIR ; 
 int /*<<< orphan*/  SDEIMR ; 
 int /*<<< orphan*/  SDEISR ; 
 int /*<<< orphan*/  SFUSE_STRAP ; 
 int /*<<< orphan*/  SOUTH_CHICKEN1 ; 
 int /*<<< orphan*/  SOUTH_CHICKEN2 ; 
 int /*<<< orphan*/  SOUTH_DSPCLK_GATE_D ; 
 int /*<<< orphan*/  SPLL_CTL ; 
 int /*<<< orphan*/  SPRCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRKEYMAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRKEYMSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRKEYVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRLINOFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPROFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRSCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRSTRIDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRSURF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRSURFLIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TILECTL ; 
 int /*<<< orphan*/  TRANSCODER_A ; 
 int /*<<< orphan*/  TRANSCODER_B ; 
 int /*<<< orphan*/  TRANSCODER_C ; 
 int /*<<< orphan*/  TRANSCODER_EDP ; 
 int /*<<< orphan*/  TRANS_CLK_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_DP_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIDEO_DIP_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIDEO_DIP_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIDEO_DIP_GCP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VBLANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEBOX_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  VSYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSYNCSHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VS_INVOCATION_COUNT ; 
 int /*<<< orphan*/  VTOTAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM0_PIPEA_ILK ; 
 int /*<<< orphan*/  WM0_PIPEB_ILK ; 
 int /*<<< orphan*/  WM0_PIPEC_IVB ; 
 int /*<<< orphan*/  WM1S_LP_ILK ; 
 int /*<<< orphan*/  WM1_LP_ILK ; 
 int /*<<< orphan*/  WM2S_LP_IVB ; 
 int /*<<< orphan*/  WM2_LP_ILK ; 
 int /*<<< orphan*/  WM3S_LP_IVB ; 
 int /*<<< orphan*/  WM3_LP_ILK ; 
 int /*<<< orphan*/  _3D_CHICKEN3 ; 
 int _DDI_BUF_TRANS_A ; 
 int _DPA_AUX_CH_CTL ; 
 int _FDI_RXA_MISC ; 
 int _FDI_RXA_TUSIZE1 ; 
 int _FDI_RXA_TUSIZE2 ; 
 int _FDI_RXB_MISC ; 
 int _FDI_RXB_TUSIZE1 ; 
 int _FDI_RXB_TUSIZE2 ; 
 int /*<<< orphan*/  _MMIO (int) ; 
 int _PCH_DPB_AUX_CH_CTL ; 
 int _PCH_DPC_AUX_CH_CTL ; 
 int _PCH_DPD_AUX_CH_CTL ; 
 int _PCH_DPLL_A ; 
 int _PCH_DPLL_B ; 
 int _PCH_FPA0 ; 
 int _PCH_FPA1 ; 
 int _PCH_FPB0 ; 
 int _PCH_FPB1 ; 
 int _PCH_TRANSACONF ; 
 int _PCH_TRANSA_DATA_M1 ; 
 int _PCH_TRANSA_DATA_M2 ; 
 int _PCH_TRANSA_DATA_N1 ; 
 int _PCH_TRANSA_DATA_N2 ; 
 int _PCH_TRANSA_LINK_M1 ; 
 int _PCH_TRANSA_LINK_M2 ; 
 int _PCH_TRANSA_LINK_N1 ; 
 int _PCH_TRANSA_LINK_N2 ; 
 int _PCH_TRANSBCONF ; 
 int _PCH_TRANS_HBLANK_A ; 
 int _PCH_TRANS_HBLANK_B ; 
 int _PCH_TRANS_HSYNC_A ; 
 int _PCH_TRANS_HSYNC_B ; 
 int _PCH_TRANS_HTOTAL_A ; 
 int _PCH_TRANS_HTOTAL_B ; 
 int _PCH_TRANS_VBLANK_A ; 
 int _PCH_TRANS_VBLANK_B ; 
 int _PCH_TRANS_VSYNCSHIFT_A ; 
 int _PCH_TRANS_VSYNCSHIFT_B ; 
 int _PCH_TRANS_VSYNC_A ; 
 int _PCH_TRANS_VSYNC_B ; 
 int _PCH_TRANS_VTOTAL_A ; 
 int _PCH_TRANS_VTOTAL_B ; 
 int /*<<< orphan*/  _PIPE_EDP ; 
 int _TRANSA_CHICKEN1 ; 
 int _TRANSA_CHICKEN2 ; 
 int _TRANSA_MSA_MISC ; 
 int _TRANSB_CHICKEN1 ; 
 int _TRANSB_CHICKEN2 ; 
 int _TRANSB_MSA_MISC ; 
 int _TRANSC_MSA_MISC ; 
 int _TRANS_DDI_FUNC_CTL_A ; 
 int _TRANS_DDI_FUNC_CTL_B ; 
 int _TRANS_DDI_FUNC_CTL_C ; 
 int _TRANS_DDI_FUNC_CTL_EDP ; 
 int _TRANS_EDP_MSA_MISC ; 
 int _WRPLL_CTL1 ; 
 int _WRPLL_CTL2 ; 
 int /*<<< orphan*/ * ddi_buf_ctl_mmio_write ; 
 int /*<<< orphan*/ * dp_aux_ch_ctl_mmio_write ; 
 int /*<<< orphan*/ * dp_tp_ctl_mmio_write ; 
 int /*<<< orphan*/ * dp_tp_status_mmio_write ; 
 int /*<<< orphan*/ * dpy_reg_mmio_read ; 
 int /*<<< orphan*/ * fdi_rx_iir_mmio_write ; 
 int /*<<< orphan*/ * fence_mmio_read ; 
 int /*<<< orphan*/ * fence_mmio_write ; 
 int /*<<< orphan*/ * fpga_dbg_mmio_write ; 
 int /*<<< orphan*/ * gamw_echo_dev_rw_ia_write ; 
 int /*<<< orphan*/ * gdrst_mmio_write ; 
 int /*<<< orphan*/ * gmbus_mmio_read ; 
 int /*<<< orphan*/ * gmbus_mmio_write ; 
 int /*<<< orphan*/ * gvt_reg_tlb_control_handler ; 
 int /*<<< orphan*/ * intel_vgpu_reg_ier_handler ; 
 int /*<<< orphan*/ * intel_vgpu_reg_iir_handler ; 
 int /*<<< orphan*/ * intel_vgpu_reg_imr_handler ; 
 int /*<<< orphan*/ * lcpll_ctl_mmio_write ; 
 int /*<<< orphan*/ * mbctl_write ; 
 int /*<<< orphan*/ * mmio_read_from_hw ; 
 int /*<<< orphan*/ * mul_force_wake_write ; 
 int /*<<< orphan*/ * pch_adpa_mmio_write ; 
 int /*<<< orphan*/ * pch_pp_control_mmio_write ; 
 int /*<<< orphan*/ * pipeconf_mmio_write ; 
 int /*<<< orphan*/ * power_well_ctl_mmio_write ; 
 int /*<<< orphan*/ * pri_surf_mmio_write ; 
 int /*<<< orphan*/ * ring_mode_mmio_write ; 
 int /*<<< orphan*/ * sbi_ctl_mmio_write ; 
 int /*<<< orphan*/ * sbi_data_mmio_read ; 
 int /*<<< orphan*/ * south_chicken2_mmio_write ; 
 int /*<<< orphan*/ * spr_surf_mmio_write ; 
 int /*<<< orphan*/ * transconf_mmio_write ; 
 int /*<<< orphan*/ * update_fdi_rx_iir_status ; 
 int /*<<< orphan*/ * vga_control_mmio_write ; 

__attribute__((used)) static int init_generic_mmio_info(struct intel_gvt *gvt)
{
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	int ret;

	MMIO_RING_DFH(RING_IMR, D_ALL, F_CMD_ACCESS, NULL,
		intel_vgpu_reg_imr_handler);

	MMIO_DFH(SDEIMR, D_ALL, 0, NULL, intel_vgpu_reg_imr_handler);
	MMIO_DFH(SDEIER, D_ALL, 0, NULL, intel_vgpu_reg_ier_handler);
	MMIO_DFH(SDEIIR, D_ALL, 0, NULL, intel_vgpu_reg_iir_handler);
	MMIO_D(SDEISR, D_ALL);

	MMIO_RING_DFH(RING_HWSTAM, D_ALL, F_CMD_ACCESS, NULL, NULL);

	MMIO_DH(GEN8_GAMW_ECO_DEV_RW_IA, D_BDW_PLUS, NULL,
		gamw_echo_dev_rw_ia_write);

	MMIO_GM_RDR(BSD_HWS_PGA_GEN7, D_ALL, NULL, NULL);
	MMIO_GM_RDR(BLT_HWS_PGA_GEN7, D_ALL, NULL, NULL);
	MMIO_GM_RDR(VEBOX_HWS_PGA_GEN7, D_ALL, NULL, NULL);

#define RING_REG(base) _MMIO((base) + 0x28)
	MMIO_RING_DFH(RING_REG, D_ALL, F_CMD_ACCESS, NULL, NULL);
#undef RING_REG

#define RING_REG(base) _MMIO((base) + 0x134)
	MMIO_RING_DFH(RING_REG, D_ALL, F_CMD_ACCESS, NULL, NULL);
#undef RING_REG

#define RING_REG(base) _MMIO((base) + 0x6c)
	MMIO_RING_DFH(RING_REG, D_ALL, 0, mmio_read_from_hw, NULL);
#undef RING_REG
	MMIO_DH(GEN7_SC_INSTDONE, D_BDW_PLUS, mmio_read_from_hw, NULL);

	MMIO_GM_RDR(_MMIO(0x2148), D_ALL, NULL, NULL);
	MMIO_GM_RDR(CCID, D_ALL, NULL, NULL);
	MMIO_GM_RDR(_MMIO(0x12198), D_ALL, NULL, NULL);
	MMIO_D(GEN7_CXT_SIZE, D_ALL);

	MMIO_RING_DFH(RING_TAIL, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_RING_DFH(RING_HEAD, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_RING_DFH(RING_CTL, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_RING_DFH(RING_ACTHD, D_ALL, F_CMD_ACCESS, mmio_read_from_hw, NULL);
	MMIO_RING_GM_RDR(RING_START, D_ALL, NULL, NULL);

	/* RING MODE */
#define RING_REG(base) _MMIO((base) + 0x29c)
	MMIO_RING_DFH(RING_REG, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL,
		ring_mode_mmio_write);
#undef RING_REG

	MMIO_RING_DFH(RING_MI_MODE, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		NULL, NULL);
	MMIO_RING_DFH(RING_INSTPM, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
			NULL, NULL);
	MMIO_RING_DFH(RING_TIMESTAMP, D_ALL, F_CMD_ACCESS,
			mmio_read_from_hw, NULL);
	MMIO_RING_DFH(RING_TIMESTAMP_UDW, D_ALL, F_CMD_ACCESS,
			mmio_read_from_hw, NULL);

	MMIO_DFH(GEN7_GT_MODE, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(CACHE_MODE_0_GEN7, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		NULL, NULL);
	MMIO_DFH(CACHE_MODE_1, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(CACHE_MODE_0, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2124), D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);

	MMIO_DFH(_MMIO(0x20dc), D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_3D_CHICKEN3, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2088), D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x20e4), D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2470), D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(GAM_ECOCHK, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(GEN7_COMMON_SLICE_CHICKEN1, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		NULL, NULL);
	MMIO_DFH(COMMON_SLICE_CHICKEN2, D_ALL, F_MODE_MASK | F_CMD_ACCESS,
		 NULL, NULL);
	MMIO_DFH(_MMIO(0x9030), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x20a0), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2420), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2430), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2434), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2438), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x243c), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x7018), D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(HALF_SLICE_CHICKEN3, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(GEN7_HALF_SLICE_CHICKEN1, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);

	/* display */
	MMIO_F(_MMIO(0x60220), 0x20, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_D(_MMIO(0x602a0), D_ALL);

	MMIO_D(_MMIO(0x65050), D_ALL);
	MMIO_D(_MMIO(0x650b4), D_ALL);

	MMIO_D(_MMIO(0xc4040), D_ALL);
	MMIO_D(DERRMR, D_ALL);

	MMIO_D(PIPEDSL(PIPE_A), D_ALL);
	MMIO_D(PIPEDSL(PIPE_B), D_ALL);
	MMIO_D(PIPEDSL(PIPE_C), D_ALL);
	MMIO_D(PIPEDSL(_PIPE_EDP), D_ALL);

	MMIO_DH(PIPECONF(PIPE_A), D_ALL, NULL, pipeconf_mmio_write);
	MMIO_DH(PIPECONF(PIPE_B), D_ALL, NULL, pipeconf_mmio_write);
	MMIO_DH(PIPECONF(PIPE_C), D_ALL, NULL, pipeconf_mmio_write);
	MMIO_DH(PIPECONF(_PIPE_EDP), D_ALL, NULL, pipeconf_mmio_write);

	MMIO_D(PIPESTAT(PIPE_A), D_ALL);
	MMIO_D(PIPESTAT(PIPE_B), D_ALL);
	MMIO_D(PIPESTAT(PIPE_C), D_ALL);
	MMIO_D(PIPESTAT(_PIPE_EDP), D_ALL);

	MMIO_D(PIPE_FLIPCOUNT_G4X(PIPE_A), D_ALL);
	MMIO_D(PIPE_FLIPCOUNT_G4X(PIPE_B), D_ALL);
	MMIO_D(PIPE_FLIPCOUNT_G4X(PIPE_C), D_ALL);
	MMIO_D(PIPE_FLIPCOUNT_G4X(_PIPE_EDP), D_ALL);

	MMIO_D(PIPE_FRMCOUNT_G4X(PIPE_A), D_ALL);
	MMIO_D(PIPE_FRMCOUNT_G4X(PIPE_B), D_ALL);
	MMIO_D(PIPE_FRMCOUNT_G4X(PIPE_C), D_ALL);
	MMIO_D(PIPE_FRMCOUNT_G4X(_PIPE_EDP), D_ALL);

	MMIO_D(CURCNTR(PIPE_A), D_ALL);
	MMIO_D(CURCNTR(PIPE_B), D_ALL);
	MMIO_D(CURCNTR(PIPE_C), D_ALL);

	MMIO_D(CURPOS(PIPE_A), D_ALL);
	MMIO_D(CURPOS(PIPE_B), D_ALL);
	MMIO_D(CURPOS(PIPE_C), D_ALL);

	MMIO_D(CURBASE(PIPE_A), D_ALL);
	MMIO_D(CURBASE(PIPE_B), D_ALL);
	MMIO_D(CURBASE(PIPE_C), D_ALL);

	MMIO_D(CUR_FBC_CTL(PIPE_A), D_ALL);
	MMIO_D(CUR_FBC_CTL(PIPE_B), D_ALL);
	MMIO_D(CUR_FBC_CTL(PIPE_C), D_ALL);

	MMIO_D(_MMIO(0x700ac), D_ALL);
	MMIO_D(_MMIO(0x710ac), D_ALL);
	MMIO_D(_MMIO(0x720ac), D_ALL);

	MMIO_D(_MMIO(0x70090), D_ALL);
	MMIO_D(_MMIO(0x70094), D_ALL);
	MMIO_D(_MMIO(0x70098), D_ALL);
	MMIO_D(_MMIO(0x7009c), D_ALL);

	MMIO_D(DSPCNTR(PIPE_A), D_ALL);
	MMIO_D(DSPADDR(PIPE_A), D_ALL);
	MMIO_D(DSPSTRIDE(PIPE_A), D_ALL);
	MMIO_D(DSPPOS(PIPE_A), D_ALL);
	MMIO_D(DSPSIZE(PIPE_A), D_ALL);
	MMIO_DH(DSPSURF(PIPE_A), D_ALL, NULL, pri_surf_mmio_write);
	MMIO_D(DSPOFFSET(PIPE_A), D_ALL);
	MMIO_D(DSPSURFLIVE(PIPE_A), D_ALL);

	MMIO_D(DSPCNTR(PIPE_B), D_ALL);
	MMIO_D(DSPADDR(PIPE_B), D_ALL);
	MMIO_D(DSPSTRIDE(PIPE_B), D_ALL);
	MMIO_D(DSPPOS(PIPE_B), D_ALL);
	MMIO_D(DSPSIZE(PIPE_B), D_ALL);
	MMIO_DH(DSPSURF(PIPE_B), D_ALL, NULL, pri_surf_mmio_write);
	MMIO_D(DSPOFFSET(PIPE_B), D_ALL);
	MMIO_D(DSPSURFLIVE(PIPE_B), D_ALL);

	MMIO_D(DSPCNTR(PIPE_C), D_ALL);
	MMIO_D(DSPADDR(PIPE_C), D_ALL);
	MMIO_D(DSPSTRIDE(PIPE_C), D_ALL);
	MMIO_D(DSPPOS(PIPE_C), D_ALL);
	MMIO_D(DSPSIZE(PIPE_C), D_ALL);
	MMIO_DH(DSPSURF(PIPE_C), D_ALL, NULL, pri_surf_mmio_write);
	MMIO_D(DSPOFFSET(PIPE_C), D_ALL);
	MMIO_D(DSPSURFLIVE(PIPE_C), D_ALL);

	MMIO_D(SPRCTL(PIPE_A), D_ALL);
	MMIO_D(SPRLINOFF(PIPE_A), D_ALL);
	MMIO_D(SPRSTRIDE(PIPE_A), D_ALL);
	MMIO_D(SPRPOS(PIPE_A), D_ALL);
	MMIO_D(SPRSIZE(PIPE_A), D_ALL);
	MMIO_D(SPRKEYVAL(PIPE_A), D_ALL);
	MMIO_D(SPRKEYMSK(PIPE_A), D_ALL);
	MMIO_DH(SPRSURF(PIPE_A), D_ALL, NULL, spr_surf_mmio_write);
	MMIO_D(SPRKEYMAX(PIPE_A), D_ALL);
	MMIO_D(SPROFFSET(PIPE_A), D_ALL);
	MMIO_D(SPRSCALE(PIPE_A), D_ALL);
	MMIO_D(SPRSURFLIVE(PIPE_A), D_ALL);

	MMIO_D(SPRCTL(PIPE_B), D_ALL);
	MMIO_D(SPRLINOFF(PIPE_B), D_ALL);
	MMIO_D(SPRSTRIDE(PIPE_B), D_ALL);
	MMIO_D(SPRPOS(PIPE_B), D_ALL);
	MMIO_D(SPRSIZE(PIPE_B), D_ALL);
	MMIO_D(SPRKEYVAL(PIPE_B), D_ALL);
	MMIO_D(SPRKEYMSK(PIPE_B), D_ALL);
	MMIO_DH(SPRSURF(PIPE_B), D_ALL, NULL, spr_surf_mmio_write);
	MMIO_D(SPRKEYMAX(PIPE_B), D_ALL);
	MMIO_D(SPROFFSET(PIPE_B), D_ALL);
	MMIO_D(SPRSCALE(PIPE_B), D_ALL);
	MMIO_D(SPRSURFLIVE(PIPE_B), D_ALL);

	MMIO_D(SPRCTL(PIPE_C), D_ALL);
	MMIO_D(SPRLINOFF(PIPE_C), D_ALL);
	MMIO_D(SPRSTRIDE(PIPE_C), D_ALL);
	MMIO_D(SPRPOS(PIPE_C), D_ALL);
	MMIO_D(SPRSIZE(PIPE_C), D_ALL);
	MMIO_D(SPRKEYVAL(PIPE_C), D_ALL);
	MMIO_D(SPRKEYMSK(PIPE_C), D_ALL);
	MMIO_DH(SPRSURF(PIPE_C), D_ALL, NULL, spr_surf_mmio_write);
	MMIO_D(SPRKEYMAX(PIPE_C), D_ALL);
	MMIO_D(SPROFFSET(PIPE_C), D_ALL);
	MMIO_D(SPRSCALE(PIPE_C), D_ALL);
	MMIO_D(SPRSURFLIVE(PIPE_C), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_A), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_A), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_A), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_A), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_A), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_A), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_A), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_A), D_ALL);
	MMIO_D(PIPESRC(TRANSCODER_A), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_B), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_B), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_B), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_B), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_B), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_B), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_B), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_B), D_ALL);
	MMIO_D(PIPESRC(TRANSCODER_B), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_C), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_C), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_C), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_C), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_C), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_C), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_C), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_C), D_ALL);
	MMIO_D(PIPESRC(TRANSCODER_C), D_ALL);

	MMIO_D(HTOTAL(TRANSCODER_EDP), D_ALL);
	MMIO_D(HBLANK(TRANSCODER_EDP), D_ALL);
	MMIO_D(HSYNC(TRANSCODER_EDP), D_ALL);
	MMIO_D(VTOTAL(TRANSCODER_EDP), D_ALL);
	MMIO_D(VBLANK(TRANSCODER_EDP), D_ALL);
	MMIO_D(VSYNC(TRANSCODER_EDP), D_ALL);
	MMIO_D(BCLRPAT(TRANSCODER_EDP), D_ALL);
	MMIO_D(VSYNCSHIFT(TRANSCODER_EDP), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_A), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_A), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_B), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_B), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_C), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_C), D_ALL);

	MMIO_D(PIPE_DATA_M1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_DATA_N1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_DATA_M2(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_DATA_N2(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_M1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_N1(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_M2(TRANSCODER_EDP), D_ALL);
	MMIO_D(PIPE_LINK_N2(TRANSCODER_EDP), D_ALL);

	MMIO_D(PF_CTL(PIPE_A), D_ALL);
	MMIO_D(PF_WIN_SZ(PIPE_A), D_ALL);
	MMIO_D(PF_WIN_POS(PIPE_A), D_ALL);
	MMIO_D(PF_VSCALE(PIPE_A), D_ALL);
	MMIO_D(PF_HSCALE(PIPE_A), D_ALL);

	MMIO_D(PF_CTL(PIPE_B), D_ALL);
	MMIO_D(PF_WIN_SZ(PIPE_B), D_ALL);
	MMIO_D(PF_WIN_POS(PIPE_B), D_ALL);
	MMIO_D(PF_VSCALE(PIPE_B), D_ALL);
	MMIO_D(PF_HSCALE(PIPE_B), D_ALL);

	MMIO_D(PF_CTL(PIPE_C), D_ALL);
	MMIO_D(PF_WIN_SZ(PIPE_C), D_ALL);
	MMIO_D(PF_WIN_POS(PIPE_C), D_ALL);
	MMIO_D(PF_VSCALE(PIPE_C), D_ALL);
	MMIO_D(PF_HSCALE(PIPE_C), D_ALL);

	MMIO_D(WM0_PIPEA_ILK, D_ALL);
	MMIO_D(WM0_PIPEB_ILK, D_ALL);
	MMIO_D(WM0_PIPEC_IVB, D_ALL);
	MMIO_D(WM1_LP_ILK, D_ALL);
	MMIO_D(WM2_LP_ILK, D_ALL);
	MMIO_D(WM3_LP_ILK, D_ALL);
	MMIO_D(WM1S_LP_ILK, D_ALL);
	MMIO_D(WM2S_LP_IVB, D_ALL);
	MMIO_D(WM3S_LP_IVB, D_ALL);

	MMIO_D(BLC_PWM_CPU_CTL2, D_ALL);
	MMIO_D(BLC_PWM_CPU_CTL, D_ALL);
	MMIO_D(BLC_PWM_PCH_CTL1, D_ALL);
	MMIO_D(BLC_PWM_PCH_CTL2, D_ALL);

	MMIO_D(_MMIO(0x48268), D_ALL);

	MMIO_F(PCH_GMBUS0, 4 * 4, 0, 0, 0, D_ALL, gmbus_mmio_read,
		gmbus_mmio_write);
	MMIO_F(PCH_GPIOA, 6 * 4, F_UNALIGN, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0xe4f00), 0x28, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_F(_MMIO(_PCH_DPB_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_PRE_SKL, NULL,
		dp_aux_ch_ctl_mmio_write);
	MMIO_F(_MMIO(_PCH_DPC_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_PRE_SKL, NULL,
		dp_aux_ch_ctl_mmio_write);
	MMIO_F(_MMIO(_PCH_DPD_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_PRE_SKL, NULL,
		dp_aux_ch_ctl_mmio_write);

	MMIO_DH(PCH_ADPA, D_PRE_SKL, NULL, pch_adpa_mmio_write);

	MMIO_DH(_MMIO(_PCH_TRANSACONF), D_ALL, NULL, transconf_mmio_write);
	MMIO_DH(_MMIO(_PCH_TRANSBCONF), D_ALL, NULL, transconf_mmio_write);

	MMIO_DH(FDI_RX_IIR(PIPE_A), D_ALL, NULL, fdi_rx_iir_mmio_write);
	MMIO_DH(FDI_RX_IIR(PIPE_B), D_ALL, NULL, fdi_rx_iir_mmio_write);
	MMIO_DH(FDI_RX_IIR(PIPE_C), D_ALL, NULL, fdi_rx_iir_mmio_write);
	MMIO_DH(FDI_RX_IMR(PIPE_A), D_ALL, NULL, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_IMR(PIPE_B), D_ALL, NULL, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_IMR(PIPE_C), D_ALL, NULL, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_CTL(PIPE_A), D_ALL, NULL, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_CTL(PIPE_B), D_ALL, NULL, update_fdi_rx_iir_status);
	MMIO_DH(FDI_RX_CTL(PIPE_C), D_ALL, NULL, update_fdi_rx_iir_status);

	MMIO_D(_MMIO(_PCH_TRANS_HTOTAL_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HBLANK_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HSYNC_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VTOTAL_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VBLANK_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNC_A), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNCSHIFT_A), D_ALL);

	MMIO_D(_MMIO(_PCH_TRANS_HTOTAL_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HBLANK_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_HSYNC_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VTOTAL_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VBLANK_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNC_B), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANS_VSYNCSHIFT_B), D_ALL);

	MMIO_D(_MMIO(_PCH_TRANSA_DATA_M1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_DATA_N1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_DATA_M2), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_DATA_N2), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_M1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_N1), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_M2), D_ALL);
	MMIO_D(_MMIO(_PCH_TRANSA_LINK_N2), D_ALL);

	MMIO_D(TRANS_DP_CTL(PIPE_A), D_ALL);
	MMIO_D(TRANS_DP_CTL(PIPE_B), D_ALL);
	MMIO_D(TRANS_DP_CTL(PIPE_C), D_ALL);

	MMIO_D(TVIDEO_DIP_CTL(PIPE_A), D_ALL);
	MMIO_D(TVIDEO_DIP_DATA(PIPE_A), D_ALL);
	MMIO_D(TVIDEO_DIP_GCP(PIPE_A), D_ALL);

	MMIO_D(TVIDEO_DIP_CTL(PIPE_B), D_ALL);
	MMIO_D(TVIDEO_DIP_DATA(PIPE_B), D_ALL);
	MMIO_D(TVIDEO_DIP_GCP(PIPE_B), D_ALL);

	MMIO_D(TVIDEO_DIP_CTL(PIPE_C), D_ALL);
	MMIO_D(TVIDEO_DIP_DATA(PIPE_C), D_ALL);
	MMIO_D(TVIDEO_DIP_GCP(PIPE_C), D_ALL);

	MMIO_D(_MMIO(_FDI_RXA_MISC), D_ALL);
	MMIO_D(_MMIO(_FDI_RXB_MISC), D_ALL);
	MMIO_D(_MMIO(_FDI_RXA_TUSIZE1), D_ALL);
	MMIO_D(_MMIO(_FDI_RXA_TUSIZE2), D_ALL);
	MMIO_D(_MMIO(_FDI_RXB_TUSIZE1), D_ALL);
	MMIO_D(_MMIO(_FDI_RXB_TUSIZE2), D_ALL);

	MMIO_DH(PCH_PP_CONTROL, D_ALL, NULL, pch_pp_control_mmio_write);
	MMIO_D(PCH_PP_DIVISOR, D_ALL);
	MMIO_D(PCH_PP_STATUS,  D_ALL);
	MMIO_D(PCH_LVDS, D_ALL);
	MMIO_D(_MMIO(_PCH_DPLL_A), D_ALL);
	MMIO_D(_MMIO(_PCH_DPLL_B), D_ALL);
	MMIO_D(_MMIO(_PCH_FPA0), D_ALL);
	MMIO_D(_MMIO(_PCH_FPA1), D_ALL);
	MMIO_D(_MMIO(_PCH_FPB0), D_ALL);
	MMIO_D(_MMIO(_PCH_FPB1), D_ALL);
	MMIO_D(PCH_DREF_CONTROL, D_ALL);
	MMIO_D(PCH_RAWCLK_FREQ, D_ALL);
	MMIO_D(PCH_DPLL_SEL, D_ALL);

	MMIO_D(_MMIO(0x61208), D_ALL);
	MMIO_D(_MMIO(0x6120c), D_ALL);
	MMIO_D(PCH_PP_ON_DELAYS, D_ALL);
	MMIO_D(PCH_PP_OFF_DELAYS, D_ALL);

	MMIO_DH(_MMIO(0xe651c), D_ALL, dpy_reg_mmio_read, NULL);
	MMIO_DH(_MMIO(0xe661c), D_ALL, dpy_reg_mmio_read, NULL);
	MMIO_DH(_MMIO(0xe671c), D_ALL, dpy_reg_mmio_read, NULL);
	MMIO_DH(_MMIO(0xe681c), D_ALL, dpy_reg_mmio_read, NULL);
	MMIO_DH(_MMIO(0xe6c04), D_ALL, dpy_reg_mmio_read, NULL);
	MMIO_DH(_MMIO(0xe6e1c), D_ALL, dpy_reg_mmio_read, NULL);

	MMIO_RO(PCH_PORT_HOTPLUG, D_ALL, 0,
		PORTA_HOTPLUG_STATUS_MASK
		| PORTB_HOTPLUG_STATUS_MASK
		| PORTC_HOTPLUG_STATUS_MASK
		| PORTD_HOTPLUG_STATUS_MASK,
		NULL, NULL);

	MMIO_DH(LCPLL_CTL, D_ALL, NULL, lcpll_ctl_mmio_write);
	MMIO_D(FUSE_STRAP, D_ALL);
	MMIO_D(DIGITAL_PORT_HOTPLUG_CNTRL, D_ALL);

	MMIO_D(DISP_ARB_CTL, D_ALL);
	MMIO_D(DISP_ARB_CTL2, D_ALL);

	MMIO_D(ILK_DISPLAY_CHICKEN1, D_ALL);
	MMIO_D(ILK_DISPLAY_CHICKEN2, D_ALL);
	MMIO_D(ILK_DSPCLK_GATE_D, D_ALL);

	MMIO_D(SOUTH_CHICKEN1, D_ALL);
	MMIO_DH(SOUTH_CHICKEN2, D_ALL, NULL, south_chicken2_mmio_write);
	MMIO_D(_MMIO(_TRANSA_CHICKEN1), D_ALL);
	MMIO_D(_MMIO(_TRANSB_CHICKEN1), D_ALL);
	MMIO_D(SOUTH_DSPCLK_GATE_D, D_ALL);
	MMIO_D(_MMIO(_TRANSA_CHICKEN2), D_ALL);
	MMIO_D(_MMIO(_TRANSB_CHICKEN2), D_ALL);

	MMIO_D(ILK_DPFC_CB_BASE, D_ALL);
	MMIO_D(ILK_DPFC_CONTROL, D_ALL);
	MMIO_D(ILK_DPFC_RECOMP_CTL, D_ALL);
	MMIO_D(ILK_DPFC_STATUS, D_ALL);
	MMIO_D(ILK_DPFC_FENCE_YOFF, D_ALL);
	MMIO_D(ILK_DPFC_CHICKEN, D_ALL);
	MMIO_D(ILK_FBC_RT_BASE, D_ALL);

	MMIO_D(IPS_CTL, D_ALL);

	MMIO_D(PIPE_CSC_COEFF_RY_GY(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BY(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RU_GU(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BU(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RV_GV(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BV(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_MODE(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_HI(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_ME(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_LO(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_HI(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_ME(PIPE_A), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_LO(PIPE_A), D_ALL);

	MMIO_D(PIPE_CSC_COEFF_RY_GY(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BY(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RU_GU(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BU(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RV_GV(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BV(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_MODE(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_HI(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_ME(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_LO(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_HI(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_ME(PIPE_B), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_LO(PIPE_B), D_ALL);

	MMIO_D(PIPE_CSC_COEFF_RY_GY(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BY(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RU_GU(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BU(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_RV_GV(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_COEFF_BV(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_MODE(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_HI(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_ME(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_PREOFF_LO(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_HI(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_ME(PIPE_C), D_ALL);
	MMIO_D(PIPE_CSC_POSTOFF_LO(PIPE_C), D_ALL);

	MMIO_D(PREC_PAL_INDEX(PIPE_A), D_ALL);
	MMIO_D(PREC_PAL_DATA(PIPE_A), D_ALL);
	MMIO_F(PREC_PAL_GC_MAX(PIPE_A, 0), 4 * 3, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_D(PREC_PAL_INDEX(PIPE_B), D_ALL);
	MMIO_D(PREC_PAL_DATA(PIPE_B), D_ALL);
	MMIO_F(PREC_PAL_GC_MAX(PIPE_B, 0), 4 * 3, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_D(PREC_PAL_INDEX(PIPE_C), D_ALL);
	MMIO_D(PREC_PAL_DATA(PIPE_C), D_ALL);
	MMIO_F(PREC_PAL_GC_MAX(PIPE_C, 0), 4 * 3, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_D(_MMIO(0x60110), D_ALL);
	MMIO_D(_MMIO(0x61110), D_ALL);
	MMIO_F(_MMIO(0x70400), 0x40, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x71400), 0x40, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x72400), 0x40, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x70440), 0xc, 0, 0, 0, D_PRE_SKL, NULL, NULL);
	MMIO_F(_MMIO(0x71440), 0xc, 0, 0, 0, D_PRE_SKL, NULL, NULL);
	MMIO_F(_MMIO(0x72440), 0xc, 0, 0, 0, D_PRE_SKL, NULL, NULL);
	MMIO_F(_MMIO(0x7044c), 0xc, 0, 0, 0, D_PRE_SKL, NULL, NULL);
	MMIO_F(_MMIO(0x7144c), 0xc, 0, 0, 0, D_PRE_SKL, NULL, NULL);
	MMIO_F(_MMIO(0x7244c), 0xc, 0, 0, 0, D_PRE_SKL, NULL, NULL);

	MMIO_D(PIPE_WM_LINETIME(PIPE_A), D_ALL);
	MMIO_D(PIPE_WM_LINETIME(PIPE_B), D_ALL);
	MMIO_D(PIPE_WM_LINETIME(PIPE_C), D_ALL);
	MMIO_D(SPLL_CTL, D_ALL);
	MMIO_D(_MMIO(_WRPLL_CTL1), D_ALL);
	MMIO_D(_MMIO(_WRPLL_CTL2), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_A), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_B), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_C), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_D), D_ALL);
	MMIO_D(PORT_CLK_SEL(PORT_E), D_ALL);
	MMIO_D(TRANS_CLK_SEL(TRANSCODER_A), D_ALL);
	MMIO_D(TRANS_CLK_SEL(TRANSCODER_B), D_ALL);
	MMIO_D(TRANS_CLK_SEL(TRANSCODER_C), D_ALL);

	MMIO_D(HSW_NDE_RSTWRN_OPT, D_ALL);
	MMIO_D(_MMIO(0x46508), D_ALL);

	MMIO_D(_MMIO(0x49080), D_ALL);
	MMIO_D(_MMIO(0x49180), D_ALL);
	MMIO_D(_MMIO(0x49280), D_ALL);

	MMIO_F(_MMIO(0x49090), 0x14, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x49190), 0x14, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x49290), 0x14, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_D(GAMMA_MODE(PIPE_A), D_ALL);
	MMIO_D(GAMMA_MODE(PIPE_B), D_ALL);
	MMIO_D(GAMMA_MODE(PIPE_C), D_ALL);

	MMIO_D(PIPE_MULT(PIPE_A), D_ALL);
	MMIO_D(PIPE_MULT(PIPE_B), D_ALL);
	MMIO_D(PIPE_MULT(PIPE_C), D_ALL);

	MMIO_D(HSW_TVIDEO_DIP_CTL(TRANSCODER_A), D_ALL);
	MMIO_D(HSW_TVIDEO_DIP_CTL(TRANSCODER_B), D_ALL);
	MMIO_D(HSW_TVIDEO_DIP_CTL(TRANSCODER_C), D_ALL);

	MMIO_DH(SFUSE_STRAP, D_ALL, NULL, NULL);
	MMIO_D(SBI_ADDR, D_ALL);
	MMIO_DH(SBI_DATA, D_ALL, sbi_data_mmio_read, NULL);
	MMIO_DH(SBI_CTL_STAT, D_ALL, NULL, sbi_ctl_mmio_write);
	MMIO_D(PIXCLK_GATE, D_ALL);

	MMIO_F(_MMIO(_DPA_AUX_CH_CTL), 6 * 4, 0, 0, 0, D_ALL, NULL,
		dp_aux_ch_ctl_mmio_write);

	MMIO_DH(DDI_BUF_CTL(PORT_A), D_ALL, NULL, ddi_buf_ctl_mmio_write);
	MMIO_DH(DDI_BUF_CTL(PORT_B), D_ALL, NULL, ddi_buf_ctl_mmio_write);
	MMIO_DH(DDI_BUF_CTL(PORT_C), D_ALL, NULL, ddi_buf_ctl_mmio_write);
	MMIO_DH(DDI_BUF_CTL(PORT_D), D_ALL, NULL, ddi_buf_ctl_mmio_write);
	MMIO_DH(DDI_BUF_CTL(PORT_E), D_ALL, NULL, ddi_buf_ctl_mmio_write);

	MMIO_DH(DP_TP_CTL(PORT_A), D_ALL, NULL, dp_tp_ctl_mmio_write);
	MMIO_DH(DP_TP_CTL(PORT_B), D_ALL, NULL, dp_tp_ctl_mmio_write);
	MMIO_DH(DP_TP_CTL(PORT_C), D_ALL, NULL, dp_tp_ctl_mmio_write);
	MMIO_DH(DP_TP_CTL(PORT_D), D_ALL, NULL, dp_tp_ctl_mmio_write);
	MMIO_DH(DP_TP_CTL(PORT_E), D_ALL, NULL, dp_tp_ctl_mmio_write);

	MMIO_DH(DP_TP_STATUS(PORT_A), D_ALL, NULL, dp_tp_status_mmio_write);
	MMIO_DH(DP_TP_STATUS(PORT_B), D_ALL, NULL, dp_tp_status_mmio_write);
	MMIO_DH(DP_TP_STATUS(PORT_C), D_ALL, NULL, dp_tp_status_mmio_write);
	MMIO_DH(DP_TP_STATUS(PORT_D), D_ALL, NULL, dp_tp_status_mmio_write);
	MMIO_DH(DP_TP_STATUS(PORT_E), D_ALL, NULL, NULL);

	MMIO_F(_MMIO(_DDI_BUF_TRANS_A), 0x50, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x64e60), 0x50, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x64eC0), 0x50, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x64f20), 0x50, 0, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x64f80), 0x50, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_D(HSW_AUD_CFG(PIPE_A), D_ALL);
	MMIO_D(HSW_AUD_PIN_ELD_CP_VLD, D_ALL);
	MMIO_D(HSW_AUD_MISC_CTRL(PIPE_A), D_ALL);

	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_A), D_ALL, NULL, NULL);
	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_B), D_ALL, NULL, NULL);
	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_C), D_ALL, NULL, NULL);
	MMIO_DH(_MMIO(_TRANS_DDI_FUNC_CTL_EDP), D_ALL, NULL, NULL);

	MMIO_D(_MMIO(_TRANSA_MSA_MISC), D_ALL);
	MMIO_D(_MMIO(_TRANSB_MSA_MISC), D_ALL);
	MMIO_D(_MMIO(_TRANSC_MSA_MISC), D_ALL);
	MMIO_D(_MMIO(_TRANS_EDP_MSA_MISC), D_ALL);

	MMIO_DH(FORCEWAKE, D_ALL, NULL, NULL);
	MMIO_D(FORCEWAKE_ACK, D_ALL);
	MMIO_D(GEN6_GT_CORE_STATUS, D_ALL);
	MMIO_D(GEN6_GT_THREAD_STATUS_REG, D_ALL);
	MMIO_DFH(GTFIFODBG, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(GTFIFOCTL, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DH(FORCEWAKE_MT, D_PRE_SKL, NULL, mul_force_wake_write);
	MMIO_DH(FORCEWAKE_ACK_HSW, D_BDW, NULL, NULL);
	MMIO_D(ECOBUS, D_ALL);
	MMIO_DH(GEN6_RC_CONTROL, D_ALL, NULL, NULL);
	MMIO_DH(GEN6_RC_STATE, D_ALL, NULL, NULL);
	MMIO_D(GEN6_RPNSWREQ, D_ALL);
	MMIO_D(GEN6_RC_VIDEO_FREQ, D_ALL);
	MMIO_D(GEN6_RP_DOWN_TIMEOUT, D_ALL);
	MMIO_D(GEN6_RP_INTERRUPT_LIMITS, D_ALL);
	MMIO_D(GEN6_RPSTAT1, D_ALL);
	MMIO_D(GEN6_RP_CONTROL, D_ALL);
	MMIO_D(GEN6_RP_UP_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RP_DOWN_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RP_CUR_UP_EI, D_ALL);
	MMIO_D(GEN6_RP_CUR_UP, D_ALL);
	MMIO_D(GEN6_RP_PREV_UP, D_ALL);
	MMIO_D(GEN6_RP_CUR_DOWN_EI, D_ALL);
	MMIO_D(GEN6_RP_CUR_DOWN, D_ALL);
	MMIO_D(GEN6_RP_PREV_DOWN, D_ALL);
	MMIO_D(GEN6_RP_UP_EI, D_ALL);
	MMIO_D(GEN6_RP_DOWN_EI, D_ALL);
	MMIO_D(GEN6_RP_IDLE_HYSTERSIS, D_ALL);
	MMIO_D(GEN6_RC1_WAKE_RATE_LIMIT, D_ALL);
	MMIO_D(GEN6_RC6_WAKE_RATE_LIMIT, D_ALL);
	MMIO_D(GEN6_RC6pp_WAKE_RATE_LIMIT, D_ALL);
	MMIO_D(GEN6_RC_EVALUATION_INTERVAL, D_ALL);
	MMIO_D(GEN6_RC_IDLE_HYSTERSIS, D_ALL);
	MMIO_D(GEN6_RC_SLEEP, D_ALL);
	MMIO_D(GEN6_RC1e_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RC6_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RC6p_THRESHOLD, D_ALL);
	MMIO_D(GEN6_RC6pp_THRESHOLD, D_ALL);
	MMIO_D(GEN6_PMINTRMSK, D_ALL);
	/*
	 * Use an arbitrary power well controlled by the PWR_WELL_CTL
	 * register.
	 */
	MMIO_DH(HSW_PWR_WELL_CTL_BIOS(HSW_DISP_PW_GLOBAL), D_BDW, NULL,
		power_well_ctl_mmio_write);
	MMIO_DH(HSW_PWR_WELL_CTL_DRIVER(HSW_DISP_PW_GLOBAL), D_BDW, NULL,
		power_well_ctl_mmio_write);
	MMIO_DH(HSW_PWR_WELL_CTL_KVMR, D_BDW, NULL, power_well_ctl_mmio_write);
	MMIO_DH(HSW_PWR_WELL_CTL_DEBUG(HSW_DISP_PW_GLOBAL), D_BDW, NULL,
		power_well_ctl_mmio_write);
	MMIO_DH(HSW_PWR_WELL_CTL5, D_BDW, NULL, power_well_ctl_mmio_write);
	MMIO_DH(HSW_PWR_WELL_CTL6, D_BDW, NULL, power_well_ctl_mmio_write);

	MMIO_D(RSTDBYCTL, D_ALL);

	MMIO_DH(GEN6_GDRST, D_ALL, NULL, gdrst_mmio_write);
	MMIO_F(FENCE_REG_GEN6_LO(0), 0x80, 0, 0, 0, D_ALL, fence_mmio_read, fence_mmio_write);
	MMIO_DH(CPU_VGACNTRL, D_ALL, NULL, vga_control_mmio_write);

	MMIO_D(TILECTL, D_ALL);

	MMIO_D(GEN6_UCGCTL1, D_ALL);
	MMIO_D(GEN6_UCGCTL2, D_ALL);

	MMIO_F(_MMIO(0x4f000), 0x90, 0, 0, 0, D_ALL, NULL, NULL);

	MMIO_D(GEN6_PCODE_DATA, D_ALL);
	MMIO_D(_MMIO(0x13812c), D_ALL);
	MMIO_DH(GEN7_ERR_INT, D_ALL, NULL, NULL);
	MMIO_D(HSW_EDRAM_CAP, D_ALL);
	MMIO_D(HSW_IDICR, D_ALL);
	MMIO_DH(GFX_FLSH_CNTL_GEN6, D_ALL, NULL, NULL);

	MMIO_D(_MMIO(0x3c), D_ALL);
	MMIO_D(_MMIO(0x860), D_ALL);
	MMIO_D(ECOSKPD, D_ALL);
	MMIO_D(_MMIO(0x121d0), D_ALL);
	MMIO_D(GEN6_BLITTER_ECOSKPD, D_ALL);
	MMIO_D(_MMIO(0x41d0), D_ALL);
	MMIO_D(GAC_ECO_BITS, D_ALL);
	MMIO_D(_MMIO(0x6200), D_ALL);
	MMIO_D(_MMIO(0x6204), D_ALL);
	MMIO_D(_MMIO(0x6208), D_ALL);
	MMIO_D(_MMIO(0x7118), D_ALL);
	MMIO_D(_MMIO(0x7180), D_ALL);
	MMIO_D(_MMIO(0x7408), D_ALL);
	MMIO_D(_MMIO(0x7c00), D_ALL);
	MMIO_DH(GEN6_MBCTL, D_ALL, NULL, mbctl_write);
	MMIO_D(_MMIO(0x911c), D_ALL);
	MMIO_D(_MMIO(0x9120), D_ALL);
	MMIO_DFH(GEN7_UCGCTL4, D_ALL, F_CMD_ACCESS, NULL, NULL);

	MMIO_D(GAB_CTL, D_ALL);
	MMIO_D(_MMIO(0x48800), D_ALL);
	MMIO_D(_MMIO(0xce044), D_ALL);
	MMIO_D(_MMIO(0xe6500), D_ALL);
	MMIO_D(_MMIO(0xe6504), D_ALL);
	MMIO_D(_MMIO(0xe6600), D_ALL);
	MMIO_D(_MMIO(0xe6604), D_ALL);
	MMIO_D(_MMIO(0xe6700), D_ALL);
	MMIO_D(_MMIO(0xe6704), D_ALL);
	MMIO_D(_MMIO(0xe6800), D_ALL);
	MMIO_D(_MMIO(0xe6804), D_ALL);
	MMIO_D(PCH_GMBUS4, D_ALL);
	MMIO_D(PCH_GMBUS5, D_ALL);

	MMIO_D(_MMIO(0x902c), D_ALL);
	MMIO_D(_MMIO(0xec008), D_ALL);
	MMIO_D(_MMIO(0xec00c), D_ALL);
	MMIO_D(_MMIO(0xec008 + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec00c + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec008 + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec00c + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec008 + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xec00c + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xec408), D_ALL);
	MMIO_D(_MMIO(0xec40c), D_ALL);
	MMIO_D(_MMIO(0xec408 + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec40c + 0x18), D_ALL);
	MMIO_D(_MMIO(0xec408 + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec40c + 0x18 * 2), D_ALL);
	MMIO_D(_MMIO(0xec408 + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xec40c + 0x18 * 3), D_ALL);
	MMIO_D(_MMIO(0xfc810), D_ALL);
	MMIO_D(_MMIO(0xfc81c), D_ALL);
	MMIO_D(_MMIO(0xfc828), D_ALL);
	MMIO_D(_MMIO(0xfc834), D_ALL);
	MMIO_D(_MMIO(0xfcc00), D_ALL);
	MMIO_D(_MMIO(0xfcc0c), D_ALL);
	MMIO_D(_MMIO(0xfcc18), D_ALL);
	MMIO_D(_MMIO(0xfcc24), D_ALL);
	MMIO_D(_MMIO(0xfd000), D_ALL);
	MMIO_D(_MMIO(0xfd00c), D_ALL);
	MMIO_D(_MMIO(0xfd018), D_ALL);
	MMIO_D(_MMIO(0xfd024), D_ALL);
	MMIO_D(_MMIO(0xfd034), D_ALL);

	MMIO_DH(FPGA_DBG, D_ALL, NULL, fpga_dbg_mmio_write);
	MMIO_D(_MMIO(0x2054), D_ALL);
	MMIO_D(_MMIO(0x12054), D_ALL);
	MMIO_D(_MMIO(0x22054), D_ALL);
	MMIO_D(_MMIO(0x1a054), D_ALL);

	MMIO_D(_MMIO(0x44070), D_ALL);
	MMIO_DFH(_MMIO(0x215c), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2178), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x217c), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x12178), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x1217c), D_ALL, F_CMD_ACCESS, NULL, NULL);

	MMIO_F(_MMIO(0x2290), 8, F_CMD_ACCESS, 0, 0, D_BDW_PLUS, NULL, NULL);
	MMIO_D(_MMIO(0x2b00), D_BDW_PLUS);
	MMIO_D(_MMIO(0x2360), D_BDW_PLUS);
	MMIO_F(_MMIO(0x5200), 32, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x5240), 32, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(_MMIO(0x5280), 16, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);

	MMIO_DFH(_MMIO(0x1c17c), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x1c178), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(BCS_SWCTRL, D_ALL, F_CMD_ACCESS, NULL, NULL);

	MMIO_F(HS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(DS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(IA_VERTICES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(IA_PRIMITIVES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(VS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(GS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(GS_PRIMITIVES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(CL_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(CL_PRIMITIVES_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(PS_INVOCATION_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_F(PS_DEPTH_COUNT, 8, F_CMD_ACCESS, 0, 0, D_ALL, NULL, NULL);
	MMIO_DH(_MMIO(0x4260), D_BDW_PLUS, NULL, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x4264), D_BDW_PLUS, NULL, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x4268), D_BDW_PLUS, NULL, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x426c), D_BDW_PLUS, NULL, gvt_reg_tlb_control_handler);
	MMIO_DH(_MMIO(0x4270), D_BDW_PLUS, NULL, gvt_reg_tlb_control_handler);
	MMIO_DFH(_MMIO(0x4094), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);

	MMIO_DFH(ARB_MODE, D_ALL, F_MODE_MASK | F_CMD_ACCESS, NULL, NULL);
	MMIO_RING_GM_RDR(RING_BBADDR, D_ALL, NULL, NULL);
	MMIO_DFH(_MMIO(0x2220), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x12220), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x22220), D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_RING_DFH(RING_SYNC_1, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_RING_DFH(RING_SYNC_0, D_ALL, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x22178), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x1a178), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x1a17c), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	MMIO_DFH(_MMIO(0x2217c), D_BDW_PLUS, F_CMD_ACCESS, NULL, NULL);
	return 0;
}