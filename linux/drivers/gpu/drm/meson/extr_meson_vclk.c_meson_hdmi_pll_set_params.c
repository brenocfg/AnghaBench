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
 unsigned int HDMI_PLL_LOCK_G12A ; 
 int HDMI_PLL_RESET ; 
 int HDMI_PLL_RESET_G12A ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL2 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL3 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL4 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL5 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL6 ; 
 int /*<<< orphan*/  HHI_HDMI_PLL_CNTL7 ; 
 int HHI_HDMI_PLL_CNTL_EN ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXBB ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXM ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 int pll_od_to_reg (unsigned int) ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void meson_hdmi_pll_set_params(struct meson_drm *priv, unsigned int m,
			       unsigned int frac, unsigned int od1,
			       unsigned int od2, unsigned int od3)
{
	unsigned int val;

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) {
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
				   0x7 << 28, HHI_HDMI_PLL_CNTL_EN);

		/* Poll for lock bit */
		regmap_read_poll_timeout(priv->hhi, HHI_HDMI_PLL_CNTL,
					 val, (val & HDMI_PLL_LOCK), 10, 0);
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) {
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
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) {
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL, 0x0b3a0400 | m);

		/* Enable and reset */
		/* TODO: add specific macro for g12a here */
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				   0x3 << 28, 0x3 << 28);

		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL2, frac);
		regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL3, 0x00000000);

		/* G12A HDMI PLL Needs specific parameters for 5.4GHz */
		if (m >= 0xf7) {
			if (frac < 0x10000) {
				regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL4,
							0x6a685c00);
				regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL5,
							0x11551293);
			} else {
				regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL4,
							0xea68dc00);
				regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL5,
							0x65771290);
			}
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x39272000);
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL7, 0x55540000);
		} else {
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL4, 0x0a691c00);
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL5, 0x33771290);
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL6, 0x39270000);
			regmap_write(priv->hhi, HHI_HDMI_PLL_CNTL7, 0x50540000);
		}

		do {
			/* Reset PLL */
			regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
					HDMI_PLL_RESET_G12A, HDMI_PLL_RESET_G12A);

			/* UN-Reset PLL */
			regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
					HDMI_PLL_RESET_G12A, 0);

			/* Poll for lock bits */
			if (!regmap_read_poll_timeout(priv->hhi,
						      HHI_HDMI_PLL_CNTL, val,
						      ((val & HDMI_PLL_LOCK_G12A)
						        == HDMI_PLL_LOCK_G12A),
						      10, 100))
				break;
		} while(1);
	}

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 16, pll_od_to_reg(od1) << 16);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 21, pll_od_to_reg(od1) << 21);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				3 << 16, pll_od_to_reg(od1) << 16);

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 22, pll_od_to_reg(od2) << 22);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 23, pll_od_to_reg(od2) << 23);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				3 << 18, pll_od_to_reg(od2) << 18);

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL2,
				3 << 18, pll_od_to_reg(od3) << 18);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL3,
				3 << 19, pll_od_to_reg(od3) << 19);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		regmap_update_bits(priv->hhi, HHI_HDMI_PLL_CNTL,
				3 << 20, pll_od_to_reg(od3) << 20);
}