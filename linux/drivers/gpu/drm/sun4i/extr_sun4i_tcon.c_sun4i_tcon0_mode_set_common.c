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
struct sun4i_tcon {int /*<<< orphan*/  regs; int /*<<< orphan*/  dclk; } ;
struct drm_display_mode {int crtc_clock; int /*<<< orphan*/  crtc_vdisplay; int /*<<< orphan*/  crtc_hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_TCON0_BASIC0_REG ; 
 int SUN4I_TCON0_BASIC0_X (int /*<<< orphan*/ ) ; 
 int SUN4I_TCON0_BASIC0_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun4i_tcon0_mode_set_common(struct sun4i_tcon *tcon,
					const struct drm_display_mode *mode)
{
	/* Configure the dot clock */
	clk_set_rate(tcon->dclk, mode->crtc_clock * 1000);

	/* Set the resolution */
	regmap_write(tcon->regs, SUN4I_TCON0_BASIC0_REG,
		     SUN4I_TCON0_BASIC0_X(mode->crtc_hdisplay) |
		     SUN4I_TCON0_BASIC0_Y(mode->crtc_vdisplay));
}