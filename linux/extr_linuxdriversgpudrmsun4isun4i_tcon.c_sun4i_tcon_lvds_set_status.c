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
typedef  int u8 ;
struct sun4i_tcon {int /*<<< orphan*/  regs; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_TCON0_LVDS_ANA0_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_LVDS_IF_EN ; 
 int /*<<< orphan*/  SUN4I_TCON0_LVDS_IF_REG ; 
 int SUN6I_TCON0_LVDS_ANA0_C (int) ; 
 int /*<<< orphan*/  SUN6I_TCON0_LVDS_ANA0_EN_DRVC ; 
 int /*<<< orphan*/  SUN6I_TCON0_LVDS_ANA0_EN_DRVD (int) ; 
 int SUN6I_TCON0_LVDS_ANA0_EN_LDO ; 
 int /*<<< orphan*/  SUN6I_TCON0_LVDS_ANA0_EN_MB ; 
 int SUN6I_TCON0_LVDS_ANA0_PD (int) ; 
 int SUN6I_TCON0_LVDS_ANA0_V (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sun4i_tcon_get_pixel_depth (struct drm_encoder const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sun4i_tcon_lvds_set_status(struct sun4i_tcon *tcon,
				       const struct drm_encoder *encoder,
				       bool enabled)
{
	if (enabled) {
		u8 val;

		regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_IF_REG,
				   SUN4I_TCON0_LVDS_IF_EN,
				   SUN4I_TCON0_LVDS_IF_EN);

		/*
		 * As their name suggest, these values only apply to the A31
		 * and later SoCs. We'll have to rework this when merging
		 * support for the older SoCs.
		 */
		regmap_write(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
			     SUN6I_TCON0_LVDS_ANA0_C(2) |
			     SUN6I_TCON0_LVDS_ANA0_V(3) |
			     SUN6I_TCON0_LVDS_ANA0_PD(2) |
			     SUN6I_TCON0_LVDS_ANA0_EN_LDO);
		udelay(2);

		regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
				   SUN6I_TCON0_LVDS_ANA0_EN_MB,
				   SUN6I_TCON0_LVDS_ANA0_EN_MB);
		udelay(2);

		regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
				   SUN6I_TCON0_LVDS_ANA0_EN_DRVC,
				   SUN6I_TCON0_LVDS_ANA0_EN_DRVC);

		if (sun4i_tcon_get_pixel_depth(encoder) == 18)
			val = 7;
		else
			val = 0xf;

		regmap_write_bits(tcon->regs, SUN4I_TCON0_LVDS_ANA0_REG,
				  SUN6I_TCON0_LVDS_ANA0_EN_DRVD(0xf),
				  SUN6I_TCON0_LVDS_ANA0_EN_DRVD(val));
	} else {
		regmap_update_bits(tcon->regs, SUN4I_TCON0_LVDS_IF_REG,
				   SUN4I_TCON0_LVDS_IF_EN, 0);
	}
}