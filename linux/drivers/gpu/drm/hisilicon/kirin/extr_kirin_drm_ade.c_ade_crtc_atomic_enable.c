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
struct kirin_crtc {int enable; struct ade_hw_ctx* hw_ctx; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct ade_hw_ctx {int /*<<< orphan*/  base; int /*<<< orphan*/  power_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  ade_display_enable (struct ade_hw_ctx*) ; 
 int /*<<< orphan*/  ade_dump_regs (int /*<<< orphan*/ ) ; 
 int ade_power_up (struct ade_hw_ctx*) ; 
 int /*<<< orphan*/  ade_set_medianoc_qos (struct ade_hw_ctx*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct kirin_crtc* to_kirin_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ade_crtc_atomic_enable(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_state)
{
	struct kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	struct ade_hw_ctx *ctx = kcrtc->hw_ctx;
	int ret;

	if (kcrtc->enable)
		return;

	if (!ctx->power_on) {
		ret = ade_power_up(ctx);
		if (ret)
			return;
	}

	ade_set_medianoc_qos(ctx);
	ade_display_enable(ctx);
	ade_dump_regs(ctx->base);
	drm_crtc_vblank_on(crtc);
	kcrtc->enable = true;
}