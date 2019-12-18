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

/* Variables and functions */
 int /*<<< orphan*/  HHI_HDMI_PHY_CNTL1 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void meson_dw_hdmi_phy_reset(struct meson_dw_hdmi *dw_hdmi)
{
	struct meson_drm *priv = dw_hdmi->priv;

	/* Enable and software reset */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1, 0xf, 0xf);

	mdelay(2);

	/* Enable and unreset */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1, 0xf, 0xe);

	mdelay(2);
}