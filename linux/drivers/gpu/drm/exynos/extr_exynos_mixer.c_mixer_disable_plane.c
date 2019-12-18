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
struct mixer_context {int /*<<< orphan*/  reg_slock; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
struct exynos_drm_plane {int /*<<< orphan*/  index; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MXR_BIT_POWERED ; 
 int /*<<< orphan*/  mixer_cfg_layer (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_disable_plane(struct exynos_drm_crtc *crtc,
				struct exynos_drm_plane *plane)
{
	struct mixer_context *mixer_ctx = crtc->ctx;
	unsigned long flags;

	DRM_DEV_DEBUG_KMS(mixer_ctx->dev, "win: %d\n", plane->index);

	if (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		return;

	spin_lock_irqsave(&mixer_ctx->reg_slock, flags);
	mixer_cfg_layer(mixer_ctx, plane->index, 0, false);
	spin_unlock_irqrestore(&mixer_ctx->reg_slock, flags);
}