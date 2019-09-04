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
struct mixer_context {int /*<<< orphan*/  flags; } ;
struct exynos_drm_plane {scalar_t__ index; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int /*<<< orphan*/  MXR_BIT_POWERED ; 
 scalar_t__ VP_DEFAULT_WIN ; 
 int /*<<< orphan*/  mixer_graph_buffer (struct mixer_context*,struct exynos_drm_plane*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp_video_buffer (struct mixer_context*,struct exynos_drm_plane*) ; 

__attribute__((used)) static void mixer_update_plane(struct exynos_drm_crtc *crtc,
			       struct exynos_drm_plane *plane)
{
	struct mixer_context *mixer_ctx = crtc->ctx;

	DRM_DEBUG_KMS("win: %d\n", plane->index);

	if (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		return;

	if (plane->index == VP_DEFAULT_WIN)
		vp_video_buffer(mixer_ctx, plane);
	else
		mixer_graph_buffer(mixer_ctx, plane);
}