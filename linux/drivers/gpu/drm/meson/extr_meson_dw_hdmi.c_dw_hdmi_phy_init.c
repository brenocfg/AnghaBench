#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct meson_dw_hdmi {TYPE_1__* data; struct meson_drm* priv; } ;
struct TYPE_4__ {scalar_t__ hdmi_use_enci; } ;
struct meson_drm {scalar_t__ io_base; TYPE_2__ venc; int /*<<< orphan*/  hhi; } ;
struct dw_hdmi {int dummy; } ;
struct drm_display_mode {int clock; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* top_write ) (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENCI_VIDEO_EN ; 
 int /*<<< orphan*/  ENCP_VIDEO_EN ; 
 int /*<<< orphan*/  HDMITX_TOP_BIST_CNTL ; 
 int /*<<< orphan*/  HDMITX_TOP_CLK_CNTL ; 
 int /*<<< orphan*/  HDMITX_TOP_SW_RESET ; 
 int /*<<< orphan*/  HDMITX_TOP_TMDS_CLK_PTTN_01 ; 
 int /*<<< orphan*/  HDMITX_TOP_TMDS_CLK_PTTN_23 ; 
 int /*<<< orphan*/  HDMITX_TOP_TMDS_CLK_PTTN_CNTL ; 
 int /*<<< orphan*/  HHI_HDMI_CLK_CNTL ; 
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL1 ; 
 int /*<<< orphan*/  HHI_MEM_PD_REG0 ; 
 unsigned int MESON_VENC_SOURCE_ENCI ; 
 unsigned int MESON_VENC_SOURCE_ENCP ; 
 int /*<<< orphan*/  VPU_HDMI_SETTING ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 scalar_t__ dw_hdmi_is_compatible (struct meson_dw_hdmi*,char*) ; 
 int /*<<< orphan*/  dw_hdmi_set_high_tmds_clock_ratio (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_top_write_bits (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  meson_dw_hdmi_phy_reset (struct meson_dw_hdmi*) ; 
 int /*<<< orphan*/  meson_hdmi_phy_setup_mode (struct meson_dw_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int dw_hdmi_phy_init(struct dw_hdmi *hdmi, void *data,
			    struct drm_display_mode *mode)
{
	struct meson_dw_hdmi *dw_hdmi = (struct meson_dw_hdmi *)data;
	struct meson_drm *priv = dw_hdmi->priv;
	unsigned int wr_clk =
		readl_relaxed(priv->io_base + _REG(VPU_HDMI_SETTING));

	DRM_DEBUG_DRIVER("\"%s\" div%d\n", mode->name,
			 mode->clock > 340000 ? 40 : 10);

	/* Enable clocks */
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL, 0xffff, 0x100);

	/* Bring HDMITX MEM output of power down */
	regmap_update_bits(priv->hhi, HHI_MEM_PD_REG0, 0xff << 8, 0);

	/* Bring out of reset */
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_SW_RESET,  0);

	/* Enable internal pixclk, tmds_clk, spdif_clk, i2s_clk, cecclk */
	dw_hdmi_top_write_bits(dw_hdmi, HDMITX_TOP_CLK_CNTL,
			       0x3, 0x3);

	/* Enable cec_clk and hdcp22_tmdsclk_en */
	dw_hdmi_top_write_bits(dw_hdmi, HDMITX_TOP_CLK_CNTL,
			       0x3 << 4, 0x3 << 4);

	/* Enable normal output to PHY */
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_BIST_CNTL, BIT(12));

	/* TMDS pattern setup (TOFIX Handle the YUV420 case) */
	if (mode->clock > 340000) {
		dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_01,
				  0);
		dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_23,
				  0x03ff03ff);
	} else {
		dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_01,
				  0x001f001f);
		dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_23,
				  0x001f001f);
	}

	/* Load TMDS pattern */
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_CNTL, 0x1);
	msleep(20);
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_CNTL, 0x2);

	/* Setup PHY parameters */
	meson_hdmi_phy_setup_mode(dw_hdmi, mode);

	/* Setup PHY */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1,
			   0xffff << 16, 0x0390 << 16);

	/* BIT_INVERT */
	if (dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxl-dw-hdmi") ||
	    dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxm-dw-hdmi") ||
	    dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-g12a-dw-hdmi"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1,
				   BIT(17), 0);
	else
		regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1,
				   BIT(17), BIT(17));

	/* Disable clock, fifo, fifo_wr */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1, 0xf, 0);

	dw_hdmi_set_high_tmds_clock_ratio(hdmi);

	msleep(100);

	/* Reset PHY 3 times in a row */
	meson_dw_hdmi_phy_reset(dw_hdmi);
	meson_dw_hdmi_phy_reset(dw_hdmi);
	meson_dw_hdmi_phy_reset(dw_hdmi);

	/* Temporary Disable VENC video stream */
	if (priv->venc.hdmi_use_enci)
		writel_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_EN));
	else
		writel_relaxed(0, priv->io_base + _REG(ENCP_VIDEO_EN));

	/* Temporary Disable HDMI video stream to HDMI-TX */
	writel_bits_relaxed(0x3, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));
	writel_bits_relaxed(0xf << 8, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	/* Re-Enable VENC video stream */
	if (priv->venc.hdmi_use_enci)
		writel_relaxed(1, priv->io_base + _REG(ENCI_VIDEO_EN));
	else
		writel_relaxed(1, priv->io_base + _REG(ENCP_VIDEO_EN));

	/* Push back HDMI clock settings */
	writel_bits_relaxed(0xf << 8, wr_clk & (0xf << 8),
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	/* Enable and Select HDMI video source for HDMI-TX */
	if (priv->venc.hdmi_use_enci)
		writel_bits_relaxed(0x3, MESON_VENC_SOURCE_ENCI,
				    priv->io_base + _REG(VPU_HDMI_SETTING));
	else
		writel_bits_relaxed(0x3, MESON_VENC_SOURCE_ENCP,
				    priv->io_base + _REG(VPU_HDMI_SETTING));

	return 0;
}