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
struct drm_plane_state {struct drm_crtc* crtc; int /*<<< orphan*/  fb; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct dc_plane_state {int /*<<< orphan*/ * in_transfer_func; } ;
struct amdgpu_framebuffer {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int amdgpu_dm_set_degamma_lut (struct drm_crtc_state*,struct dc_plane_state*) ; 
 int /*<<< orphan*/  dc_transfer_func_release (int /*<<< orphan*/ *) ; 
 int fill_plane_attributes_from_fb (int /*<<< orphan*/ ,struct dc_plane_state*,struct amdgpu_framebuffer const*) ; 
 int /*<<< orphan*/  fill_rects_from_plane_state (struct drm_plane_state*,struct dc_plane_state*) ; 
 struct amdgpu_framebuffer* to_amdgpu_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_plane_attributes(struct amdgpu_device *adev,
				 struct dc_plane_state *dc_plane_state,
				 struct drm_plane_state *plane_state,
				 struct drm_crtc_state *crtc_state)
{
	const struct amdgpu_framebuffer *amdgpu_fb =
		to_amdgpu_framebuffer(plane_state->fb);
	const struct drm_crtc *crtc = plane_state->crtc;
	int ret = 0;

	if (!fill_rects_from_plane_state(plane_state, dc_plane_state))
		return -EINVAL;

	ret = fill_plane_attributes_from_fb(
		crtc->dev->dev_private,
		dc_plane_state,
		amdgpu_fb);

	if (ret)
		return ret;

	/*
	 * Always set input transfer function, since plane state is refreshed
	 * every time.
	 */
	ret = amdgpu_dm_set_degamma_lut(crtc_state, dc_plane_state);
	if (ret) {
		dc_transfer_func_release(dc_plane_state->in_transfer_func);
		dc_plane_state->in_transfer_func = NULL;
	}

	return ret;
}