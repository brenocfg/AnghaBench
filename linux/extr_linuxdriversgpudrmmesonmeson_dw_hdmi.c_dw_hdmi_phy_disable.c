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
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL0 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_phy_disable(struct dw_hdmi *hdmi,
				void *data)
{
	struct meson_dw_hdmi *dw_hdmi = (struct meson_dw_hdmi *)data;
	struct meson_drm *priv = dw_hdmi->priv;

	DRM_DEBUG_DRIVER("\n");

	regmap_write(priv->hhi, HHI_HDMI_PHY_CNTL0, 0);
}