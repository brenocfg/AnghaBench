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
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {int /*<<< orphan*/  vblank_lock; int /*<<< orphan*/  frame_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECON_UPDATE ; 
 int /*<<< orphan*/  STANDALONE_UPDATE_F ; 
 int /*<<< orphan*/  decon_get_frame_count (struct decon_context*,int) ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_shadow_protect (struct decon_context*,int) ; 
 int /*<<< orphan*/  exynos_crtc_handle_event (struct exynos_drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void decon_atomic_flush(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	unsigned long flags;

	spin_lock_irqsave(&ctx->vblank_lock, flags);

	decon_shadow_protect(ctx, false);

	decon_set_bits(ctx, DECON_UPDATE, STANDALONE_UPDATE_F, ~0);

	ctx->frame_id = decon_get_frame_count(ctx, true);

	exynos_crtc_handle_event(crtc);

	spin_unlock_irqrestore(&ctx->vblank_lock, flags);
}