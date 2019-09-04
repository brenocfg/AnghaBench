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
struct vidi_context {int suspended; int /*<<< orphan*/  lock; } ;
struct exynos_drm_crtc {int /*<<< orphan*/  base; struct vidi_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_vblank_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vidi_enable(struct exynos_drm_crtc *crtc)
{
	struct vidi_context *ctx = crtc->ctx;

	mutex_lock(&ctx->lock);

	ctx->suspended = false;

	mutex_unlock(&ctx->lock);

	drm_crtc_vblank_on(&crtc->base);
}