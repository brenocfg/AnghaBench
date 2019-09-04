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
struct meson_drm {int /*<<< orphan*/  hhi; } ;

/* Variables and functions */
 unsigned int HDMI_PLL_LOCK ; 
 int HDMI_PLL_RESET ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL2 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL3 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL4 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL5 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL6 ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,char*) ; 
 int pll_od_to_reg (unsigned int) ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void meson_hdmi_pll_set_params(struct meson_drm *priv, unsigned int m,
			       unsigned int frac, unsigned int od1,
			       unsigned int od2, unsigned int od3)
{
	unsigned int val;

	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxbb-vpu")) {
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL, 0x58000200 | m);
		if (frac)
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL2,
				     0x00004000 | frac);
		else
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL2,
				     0x00000000);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x0d5c5091);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x801da72c);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x71486980);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x00000e55);

		/* Enable and unreset */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				   0x7 << 28, 0x4 << 28);

		/* Poll for lock bit */
		regmap_read_poll_timeout(priv->hhi, HHI_HDMI_PLL_CNTL,
					 val, (val & HDMI_PLL_LOCK), 10, 0);
	} else if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu") ||
		   meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu")) {
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL, 0x40000200 | m);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL2, 0x800cb000 | frac);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x860f30c4);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x0c8e0000);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x001fa729);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x01a31500);

		/* Reset PLL */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				HDMI_PLL_RESET, HDMI_PLL_RESET);
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				HDMI_PLL_RESET, 0);

		/* Poll for lock bit */
		regmap_read_poll_timeout(priv->hhi, HHI_HDMI_PLL_CNTL, val,
				(val & HDMI_PLL_LOCK), 10, 0);
	}

	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxbb-vpu"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 16, pll_od_to_reg(od1) << 16);
	else if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu") ||
			meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 21, pll_od_to_reg(od1) << 21);

	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxbb-vpu"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 22, pll_od_to_reg(od2) << 22);
	else if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu") ||
			meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 23, pll_od_to_reg(od2) << 23);

	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxbb-vpu"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 18, pll_od_to_reg(od3) << 18);
	else if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu") ||
			meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 19, pll_od_to_reg(od3) << 19);

}