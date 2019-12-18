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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ current_mode; } ;
struct meson_drm {TYPE_1__ venc; scalar_t__ io_base; } ;
struct meson_cvbs_enci_mode {scalar_t__ mode_tag; int hso_begin; int hso_end; int vso_even; int vso_odd; int video_prog_mode; int video_mode; int yc_delay; int pixel_start; int pixel_end; int top_field_line_start; int top_field_line_end; int bottom_field_line_start; int bottom_field_line_end; int video_saturation; int video_contrast; int video_brightness; int video_hue; int analog_sync_adj; int /*<<< orphan*/  sch_adjust; int /*<<< orphan*/  macv_max_amp; } ;

/* Variables and functions */
 int ENCI_CFILT_CMPT_CB_DLY (int) ; 
 int ENCI_CFILT_CMPT_CR_DLY (int) ; 
 int ENCI_CFILT_CMPT_SEL_HIGH ; 
 int /*<<< orphan*/  ENCI_CFILT_CTRL ; 
 int /*<<< orphan*/  ENCI_CFILT_CTRL2 ; 
 int /*<<< orphan*/  ENCI_DACSEL_0 ; 
 int /*<<< orphan*/  ENCI_DACSEL_1 ; 
 int /*<<< orphan*/  ENCI_DBG_PX_RST ; 
 int /*<<< orphan*/  ENCI_MACV_MAX_AMP ; 
 int ENCI_MACV_MAX_AMP_ENABLE_CHANGE ; 
 int ENCI_MACV_MAX_AMP_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENCI_MACV_N0 ; 
 int /*<<< orphan*/  ENCI_SYNC_ADJ ; 
 int /*<<< orphan*/  ENCI_SYNC_HSO_BEGIN ; 
 int /*<<< orphan*/  ENCI_SYNC_HSO_END ; 
 int /*<<< orphan*/  ENCI_SYNC_MODE ; 
 int /*<<< orphan*/  ENCI_SYNC_VSO_EVNLN ; 
 int /*<<< orphan*/  ENCI_SYNC_VSO_ODDLN ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_CTL ; 
 int ENCI_VFIFO2VD_CTL_ENABLE ; 
 int ENCI_VFIFO2VD_CTL_VD_SEL (int) ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_LINE_BOT_END ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_LINE_BOT_START ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_LINE_TOP_END ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_LINE_TOP_START ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_PIXEL_END ; 
 int /*<<< orphan*/  ENCI_VFIFO2VD_PIXEL_START ; 
 int /*<<< orphan*/  ENCI_VIDEO_BRIGHT ; 
 int /*<<< orphan*/  ENCI_VIDEO_CONT ; 
 int /*<<< orphan*/  ENCI_VIDEO_EN ; 
 int ENCI_VIDEO_EN_ENABLE ; 
 int /*<<< orphan*/  ENCI_VIDEO_HUE ; 
 int /*<<< orphan*/  ENCI_VIDEO_MODE ; 
 int /*<<< orphan*/  ENCI_VIDEO_MODE_ADV ; 
 int ENCI_VIDEO_MODE_ADV_DMXMD (int) ; 
 int ENCI_VIDEO_MODE_ADV_VBICTL_LINE_17_22 ; 
 int ENCI_VIDEO_MODE_ADV_YBW_HIGH ; 
 int /*<<< orphan*/  ENCI_VIDEO_SAT ; 
 int /*<<< orphan*/  ENCI_VIDEO_SCH ; 
 int /*<<< orphan*/  ENCI_YC_DELAY ; 
 int /*<<< orphan*/  MESON_VIU_VPP_MUX_ENCI ; 
 int /*<<< orphan*/  VENC_DVI_SETTING ; 
 int /*<<< orphan*/  VENC_SYNC_ROUTE ; 
 int /*<<< orphan*/  VENC_UPSAMPLE_CTRL0 ; 
 int /*<<< orphan*/  VENC_UPSAMPLE_CTRL1 ; 
 int /*<<< orphan*/  VENC_UPSAMPLE_CTRL2 ; 
 int VENC_UPSAMPLE_CTRL_F0_2_CLK_RATIO ; 
 int VENC_UPSAMPLE_CTRL_F1_EN ; 
 int VENC_UPSAMPLE_CTRL_F1_UPSAMPLE_EN ; 
 int VENC_UPSAMPLE_CTRL_INTERLACE_HIGH_LUMA ; 
 int VENC_UPSAMPLE_CTRL_INTERLACE_PB ; 
 int VENC_UPSAMPLE_CTRL_INTERLACE_PR ; 
 int /*<<< orphan*/  VENC_VDAC_DAC0_FILT_CTRL0 ; 
 int VENC_VDAC_DAC0_FILT_CTRL0_EN ; 
 int /*<<< orphan*/  VENC_VDAC_DAC0_FILT_CTRL1 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL0 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL1 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL2 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL3 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL4 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL5 ; 
 int /*<<< orphan*/  VENC_VDAC_FIFO_CTRL ; 
 int VENC_VDAC_FIFO_EN_ENCI_ENABLE ; 
 int /*<<< orphan*/  VENC_VDAC_SETTING ; 
 int /*<<< orphan*/  VENC_VIDEO_PROG_MODE ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_vpp_setup_mux (struct meson_drm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_venci_cvbs_mode_set(struct meson_drm *priv,
			       struct meson_cvbs_enci_mode *mode)
{
	u32 reg;

	if (mode->mode_tag == priv->venc.current_mode)
		return;

	/* CVBS Filter settings */
	writel_relaxed(ENCI_CFILT_CMPT_SEL_HIGH | 0x10,
		       priv->io_base + _REG(ENCI_CFILT_CTRL));
	writel_relaxed(ENCI_CFILT_CMPT_CR_DLY(2) |
		       ENCI_CFILT_CMPT_CB_DLY(1),
		       priv->io_base + _REG(ENCI_CFILT_CTRL2));

	/* Digital Video Select : Interlace, clk27 clk, external */
	writel_relaxed(0, priv->io_base + _REG(VENC_DVI_SETTING));

	/* Reset Video Mode */
	writel_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_MODE));
	writel_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_MODE_ADV));

	/* Horizontal sync signal output */
	writel_relaxed(mode->hso_begin,
			priv->io_base + _REG(ENCI_SYNC_HSO_BEGIN));
	writel_relaxed(mode->hso_end,
			priv->io_base + _REG(ENCI_SYNC_HSO_END));

	/* Vertical Sync lines */
	writel_relaxed(mode->vso_even,
			priv->io_base + _REG(ENCI_SYNC_VSO_EVNLN));
	writel_relaxed(mode->vso_odd,
			priv->io_base + _REG(ENCI_SYNC_VSO_ODDLN));

	/* Macrovision max amplitude change */
	writel_relaxed(ENCI_MACV_MAX_AMP_ENABLE_CHANGE |
		       ENCI_MACV_MAX_AMP_VAL(mode->macv_max_amp),
		       priv->io_base + _REG(ENCI_MACV_MAX_AMP));

	/* Video mode */
	writel_relaxed(mode->video_prog_mode,
			priv->io_base + _REG(VENC_VIDEO_PROG_MODE));
	writel_relaxed(mode->video_mode,
			priv->io_base + _REG(ENCI_VIDEO_MODE));

	/*
	 * Advanced Video Mode :
	 * Demux shifting 0x2
	 * Blank line end at line17/22
	 * High bandwidth Luma Filter
	 * Low bandwidth Chroma Filter
	 * Bypass luma low pass filter
	 * No macrovision on CSYNC
	 */
	writel_relaxed(ENCI_VIDEO_MODE_ADV_DMXMD(2) |
		       ENCI_VIDEO_MODE_ADV_VBICTL_LINE_17_22 |
		       ENCI_VIDEO_MODE_ADV_YBW_HIGH,
		       priv->io_base + _REG(ENCI_VIDEO_MODE_ADV));

	writel(mode->sch_adjust, priv->io_base + _REG(ENCI_VIDEO_SCH));

	/* Sync mode : MASTER Master mode, free run, send HSO/VSO out */
	writel_relaxed(0x07, priv->io_base + _REG(ENCI_SYNC_MODE));

	/* 0x3 Y, C, and Component Y delay */
	writel_relaxed(mode->yc_delay, priv->io_base + _REG(ENCI_YC_DELAY));

	/* Timings */
	writel_relaxed(mode->pixel_start,
			priv->io_base + _REG(ENCI_VFIFO2VD_PIXEL_START));
	writel_relaxed(mode->pixel_end,
			priv->io_base + _REG(ENCI_VFIFO2VD_PIXEL_END));

	writel_relaxed(mode->top_field_line_start,
			priv->io_base + _REG(ENCI_VFIFO2VD_LINE_TOP_START));
	writel_relaxed(mode->top_field_line_end,
			priv->io_base + _REG(ENCI_VFIFO2VD_LINE_TOP_END));

	writel_relaxed(mode->bottom_field_line_start,
			priv->io_base + _REG(ENCI_VFIFO2VD_LINE_BOT_START));
	writel_relaxed(mode->bottom_field_line_end,
			priv->io_base + _REG(ENCI_VFIFO2VD_LINE_BOT_END));

	/* Internal Venc, Internal VIU Sync, Internal Vencoder */
	writel_relaxed(0, priv->io_base + _REG(VENC_SYNC_ROUTE));

	/* UNreset Interlaced TV Encoder */
	writel_relaxed(0, priv->io_base + _REG(ENCI_DBG_PX_RST));

	/*
	 * Enable Vfifo2vd and set Y_Cb_Y_Cr:
	 * Corresponding value:
	 * Y  => 00 or 10
	 * Cb => 01
	 * Cr => 11
	 * Ex: 0x4e => 01001110 would mean Cb/Y/Cr/Y
	 */
	writel_relaxed(ENCI_VFIFO2VD_CTL_ENABLE |
		       ENCI_VFIFO2VD_CTL_VD_SEL(0x4e),
		       priv->io_base + _REG(ENCI_VFIFO2VD_CTL));

	/* Power UP Dacs */
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_SETTING));

	/* Video Upsampling */
	/*
	 * CTRL0, CTRL1 and CTRL2:
	 * Filter0: input data sample every 2 cloks
	 * Filter1: filtering and upsample enable
	 */
	reg = VENC_UPSAMPLE_CTRL_F0_2_CLK_RATIO | VENC_UPSAMPLE_CTRL_F1_EN |
		VENC_UPSAMPLE_CTRL_F1_UPSAMPLE_EN;

	/*
	 * Upsample CTRL0:
	 * Interlace High Bandwidth Luma
	 */
	writel_relaxed(VENC_UPSAMPLE_CTRL_INTERLACE_HIGH_LUMA | reg,
		       priv->io_base + _REG(VENC_UPSAMPLE_CTRL0));

	/*
	 * Upsample CTRL1:
	 * Interlace Pb
	 */
	writel_relaxed(VENC_UPSAMPLE_CTRL_INTERLACE_PB | reg,
		       priv->io_base + _REG(VENC_UPSAMPLE_CTRL1));

	/*
	 * Upsample CTRL2:
	 * Interlace R
	 */
	writel_relaxed(VENC_UPSAMPLE_CTRL_INTERLACE_PR | reg,
		       priv->io_base + _REG(VENC_UPSAMPLE_CTRL2));

	/* Select Interlace Y DACs */
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_DACSEL0));
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_DACSEL1));
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_DACSEL2));
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_DACSEL3));
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_DACSEL4));
	writel_relaxed(0, priv->io_base + _REG(VENC_VDAC_DACSEL5));

	/* Select ENCI for VIU */
	meson_vpp_setup_mux(priv, MESON_VIU_VPP_MUX_ENCI);

	/* Enable ENCI FIFO */
	writel_relaxed(VENC_VDAC_FIFO_EN_ENCI_ENABLE,
		       priv->io_base + _REG(VENC_VDAC_FIFO_CTRL));

	/* Select ENCI DACs 0, 1, 4, and 5 */
	writel_relaxed(0x11, priv->io_base + _REG(ENCI_DACSEL_0));
	writel_relaxed(0x11, priv->io_base + _REG(ENCI_DACSEL_1));

	/* Interlace video enable */
	writel_relaxed(ENCI_VIDEO_EN_ENABLE,
		       priv->io_base + _REG(ENCI_VIDEO_EN));

	/* Configure Video Saturation / Contrast / Brightness / Hue */
	writel_relaxed(mode->video_saturation,
			priv->io_base + _REG(ENCI_VIDEO_SAT));
	writel_relaxed(mode->video_contrast,
			priv->io_base + _REG(ENCI_VIDEO_CONT));
	writel_relaxed(mode->video_brightness,
			priv->io_base + _REG(ENCI_VIDEO_BRIGHT));
	writel_relaxed(mode->video_hue,
			priv->io_base + _REG(ENCI_VIDEO_HUE));

	/* Enable DAC0 Filter */
	writel_relaxed(VENC_VDAC_DAC0_FILT_CTRL0_EN,
		       priv->io_base + _REG(VENC_VDAC_DAC0_FILT_CTRL0));
	writel_relaxed(0xfc48, priv->io_base + _REG(VENC_VDAC_DAC0_FILT_CTRL1));

	/* 0 in Macrovision register 0 */
	writel_relaxed(0, priv->io_base + _REG(ENCI_MACV_N0));

	/* Analog Synchronization and color burst value adjust */
	writel_relaxed(mode->analog_sync_adj,
			priv->io_base + _REG(ENCI_SYNC_ADJ));

	priv->venc.current_mode = mode->mode_tag;
}