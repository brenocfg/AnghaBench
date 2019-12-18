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
struct vop {int /*<<< orphan*/  dclk; } ;
struct drm_display_mode {int clock; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_round_rate (int /*<<< orphan*/ ,int) ; 
 struct vop* to_vop (struct drm_crtc*) ; 

__attribute__((used)) static bool vop_crtc_mode_fixup(struct drm_crtc *crtc,
				const struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	struct vop *vop = to_vop(crtc);

	adjusted_mode->clock =
		DIV_ROUND_UP(clk_round_rate(vop->dclk,
					    adjusted_mode->clock * 1000), 1000);

	return true;
}