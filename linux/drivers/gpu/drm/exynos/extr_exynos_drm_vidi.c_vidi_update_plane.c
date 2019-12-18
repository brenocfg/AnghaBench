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
struct vidi_context {int /*<<< orphan*/  dev; scalar_t__ suspended; } ;
struct TYPE_2__ {struct drm_plane_state* state; } ;
struct exynos_drm_plane {TYPE_1__ base; } ;
struct exynos_drm_crtc {struct vidi_context* ctx; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_drm_fb_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vidi_update_plane(struct exynos_drm_crtc *crtc,
			      struct exynos_drm_plane *plane)
{
	struct drm_plane_state *state = plane->base.state;
	struct vidi_context *ctx = crtc->ctx;
	dma_addr_t addr;

	if (ctx->suspended)
		return;

	addr = exynos_drm_fb_dma_addr(state->fb, 0);
	DRM_DEV_DEBUG_KMS(ctx->dev, "dma_addr = %pad\n", &addr);
}