#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ingenic_drm {int /*<<< orphan*/  pix_clk; } ;
struct TYPE_2__ {int clock; } ;
struct drm_crtc_state {TYPE_1__ adjusted_mode; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 long clk_round_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 struct ingenic_drm* drm_crtc_get_priv (struct drm_crtc*) ; 

__attribute__((used)) static int ingenic_drm_crtc_atomic_check(struct drm_crtc *crtc,
					 struct drm_crtc_state *state)
{
	struct ingenic_drm *priv = drm_crtc_get_priv(crtc);
	long rate;

	if (!drm_atomic_crtc_needs_modeset(state))
		return 0;

	rate = clk_round_rate(priv->pix_clk,
			      state->adjusted_mode.clock * 1000);
	if (rate < 0)
		return rate;

	return 0;
}