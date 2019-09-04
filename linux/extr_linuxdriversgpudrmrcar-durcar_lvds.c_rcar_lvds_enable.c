#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* encoder; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct rcar_lvds {int enabled; int mode; scalar_t__ panel; TYPE_3__* info; int /*<<< orphan*/  clock; TYPE_2__ bridge; struct drm_display_mode display_mode; } ;
struct drm_crtc {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_6__ {int quirks; int gen; } ;
struct TYPE_4__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVDCHCR ; 
 int LVDCHCR_CHSEL_CH (int,int) ; 
 int /*<<< orphan*/  LVDCR0 ; 
 int LVDCR0_BEN ; 
 int LVDCR0_DUSEL ; 
 int LVDCR0_LVEN ; 
 int LVDCR0_LVMD_SHIFT ; 
 int LVDCR0_LVRES ; 
 int LVDCR0_PLLON ; 
 int LVDCR0_PWD ; 
 int /*<<< orphan*/  LVDCR1 ; 
 int LVDCR1_CHSTBY (int) ; 
 int LVDCR1_CLKSTBY ; 
 int /*<<< orphan*/  LVDCTRCR ; 
 int LVDCTRCR_CTR0SEL_HSYNC ; 
 int LVDCTRCR_CTR1SEL_VSYNC ; 
 int LVDCTRCR_CTR2SEL_DISP ; 
 int LVDCTRCR_CTR3SEL_ZERO ; 
 int /*<<< orphan*/  LVDPLLCR ; 
 int RCAR_LVDS_QUIRK_GEN2_PLLCR ; 
 int RCAR_LVDS_QUIRK_GEN3_LVEN ; 
 int RCAR_LVDS_QUIRK_LANES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_panel_enable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_prepare (scalar_t__) ; 
 int rcar_lvds_lvdpllcr_gen2 (int /*<<< orphan*/ ) ; 
 int rcar_lvds_lvdpllcr_gen3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_lvds_write (struct rcar_lvds*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rcar_lvds_enable(struct drm_bridge *bridge)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	const struct drm_display_mode *mode = &lvds->display_mode;
	/*
	 * FIXME: We should really retrieve the CRTC through the state, but how
	 * do we get a state pointer?
	 */
	struct drm_crtc *crtc = lvds->bridge.encoder->crtc;
	u32 lvdpllcr;
	u32 lvdhcr;
	u32 lvdcr0;
	int ret;

	WARN_ON(lvds->enabled);

	ret = clk_prepare_enable(lvds->clock);
	if (ret < 0)
		return;

	/*
	 * Hardcode the channels and control signals routing for now.
	 *
	 * HSYNC -> CTRL0
	 * VSYNC -> CTRL1
	 * DISP  -> CTRL2
	 * 0     -> CTRL3
	 */
	rcar_lvds_write(lvds, LVDCTRCR, LVDCTRCR_CTR3SEL_ZERO |
			LVDCTRCR_CTR2SEL_DISP | LVDCTRCR_CTR1SEL_VSYNC |
			LVDCTRCR_CTR0SEL_HSYNC);

	if (lvds->info->quirks & RCAR_LVDS_QUIRK_LANES)
		lvdhcr = LVDCHCR_CHSEL_CH(0, 0) | LVDCHCR_CHSEL_CH(1, 3)
		       | LVDCHCR_CHSEL_CH(2, 2) | LVDCHCR_CHSEL_CH(3, 1);
	else
		lvdhcr = LVDCHCR_CHSEL_CH(0, 0) | LVDCHCR_CHSEL_CH(1, 1)
		       | LVDCHCR_CHSEL_CH(2, 2) | LVDCHCR_CHSEL_CH(3, 3);

	rcar_lvds_write(lvds, LVDCHCR, lvdhcr);

	/* PLL clock configuration. */
	if (lvds->info->quirks & RCAR_LVDS_QUIRK_GEN2_PLLCR)
		lvdpllcr = rcar_lvds_lvdpllcr_gen2(mode->clock);
	else
		lvdpllcr = rcar_lvds_lvdpllcr_gen3(mode->clock);
	rcar_lvds_write(lvds, LVDPLLCR, lvdpllcr);

	/* Set the LVDS mode and select the input. */
	lvdcr0 = lvds->mode << LVDCR0_LVMD_SHIFT;
	if (drm_crtc_index(crtc) == 2)
		lvdcr0 |= LVDCR0_DUSEL;
	rcar_lvds_write(lvds, LVDCR0, lvdcr0);

	/* Turn all the channels on. */
	rcar_lvds_write(lvds, LVDCR1,
			LVDCR1_CHSTBY(3) | LVDCR1_CHSTBY(2) |
			LVDCR1_CHSTBY(1) | LVDCR1_CHSTBY(0) | LVDCR1_CLKSTBY);

	if (lvds->info->gen < 3) {
		/* Enable LVDS operation and turn the bias circuitry on. */
		lvdcr0 |= LVDCR0_BEN | LVDCR0_LVEN;
		rcar_lvds_write(lvds, LVDCR0, lvdcr0);
	}

	/* Turn the PLL on. */
	lvdcr0 |= LVDCR0_PLLON;
	rcar_lvds_write(lvds, LVDCR0, lvdcr0);

	if (lvds->info->gen > 2) {
		/* Set LVDS normal mode. */
		lvdcr0 |= LVDCR0_PWD;
		rcar_lvds_write(lvds, LVDCR0, lvdcr0);
	}

	if (lvds->info->quirks & RCAR_LVDS_QUIRK_GEN3_LVEN) {
		/* Turn on the LVDS PHY. */
		lvdcr0 |= LVDCR0_LVEN;
		rcar_lvds_write(lvds, LVDCR0, lvdcr0);
	}

	/* Wait for the startup delay. */
	usleep_range(100, 150);

	/* Turn the output on. */
	lvdcr0 |= LVDCR0_LVRES;
	rcar_lvds_write(lvds, LVDCR0, lvdcr0);

	if (lvds->panel) {
		drm_panel_prepare(lvds->panel);
		drm_panel_enable(lvds->panel);
	}

	lvds->enabled = true;
}