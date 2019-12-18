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
struct meson_dw_hdmi {struct meson_drm* priv; } ;
struct meson_drm {int /*<<< orphan*/  hhi; } ;
struct drm_display_mode {unsigned int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL0 ; 
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL3 ; 
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL5 ; 
 scalar_t__ dw_hdmi_is_compatible (struct meson_dw_hdmi*,char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void meson_hdmi_phy_setup_mode(struct meson_dw_hdmi *dw_hdmi,
				      struct drm_display_mode *mode)
{
	struct meson_drm *priv = dw_hdmi->priv;
	unsigned int pixel_clock = mode->clock;

	if (dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxl-dw-hdmi") ||
	    dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxm-dw-hdmi")) {
		if (pixel_clock >= 371250) {
			/* 5.94Gbps, 3.7125Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x333d3282);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2136315b);
		} else if (pixel_clock >= 297000) {
			/* 2.97Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33303382);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2036315b);
		} else if (pixel_clock >= 148500) {
			/* 1.485Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33303362);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2016315b);
		} else {
			/* 742.5Mbps, and below */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33604142);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x0016315b);
		}
	} else if (dw_hdmi_is_compatible(dw_hdmi,
					 "amlogic,meson-gxbb-dw-hdmi")) {
		if (pixel_clock >= 371250) {
			/* 5.94Gbps, 3.7125Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33353245);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2100115b);
		} else if (pixel_clock >= 297000) {
			/* 2.97Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33634283);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0xb000115b);
		} else {
			/* 1.485Gbps, and below */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33632122);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2000115b);
		}
	} else if (dw_hdmi_is_compatible(dw_hdmi,
					 "amlogic,meson-g12a-dw-hdmi")) {
		if (pixel_clock >= 371250) {
			/* 5.94Gbps, 3.7125Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x37eb65c4);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2ab0ff3b);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL5, 0x0000080b);
		} else if (pixel_clock >= 297000) {
			/* 2.97Gbps */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33eb6262);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2ab0ff3b);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL5, 0x00000003);
		} else {
			/* 1.485Gbps, and below */
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33eb4242);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2ab0ff3b);
			regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL5, 0x00000003);
		}
	}
}