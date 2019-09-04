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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct ade_hw_ctx {int /*<<< orphan*/  base; int /*<<< orphan*/  power_on; } ;
struct ade_crtc {int enable; struct ade_hw_ctx* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ade_display_enable (struct ade_crtc*) ; 
 int /*<<< orphan*/  ade_dump_regs (int /*<<< orphan*/ ) ; 
 int ade_power_up (struct ade_hw_ctx*) ; 
 int /*<<< orphan*/  ade_set_medianoc_qos (struct ade_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct ade_crtc* to_ade_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ade_crtc_atomic_enable(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_state)
{
	struct ade_crtc *acrtc = to_ade_crtc(crtc);
	struct ade_hw_ctx *ctx = acrtc->ctx;
	int ret;

	if (acrtc->enable)
		return;

	if (!ctx->power_on) {
		ret = ade_power_up(ctx);
		if (ret)
			return;
	}

	ade_set_medianoc_qos(acrtc);
	ade_display_enable(acrtc);
	ade_dump_regs(ctx->base);
	drm_crtc_vblank_on(crtc);
	acrtc->enable = true;
}