#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_crtc_state {scalar_t__ active; scalar_t__ enable; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct dm_crtc_state {scalar_t__ active_planes; int /*<<< orphan*/  stream; } ;
struct dc {int dummy; } ;
struct TYPE_4__ {struct dc* dc; } ;
struct amdgpu_device {TYPE_2__ dm; } ;
struct TYPE_3__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ DC_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ dc_validate_stream (struct dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_update_crtc_interrupt_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 scalar_t__ does_crtc_have_active_cursor (struct drm_crtc_state*) ; 
 scalar_t__ modeset_required (struct drm_crtc_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dm_crtc_state* to_dm_crtc_state (struct drm_crtc_state*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dm_crtc_helper_atomic_check(struct drm_crtc *crtc,
				       struct drm_crtc_state *state)
{
	struct amdgpu_device *adev = crtc->dev->dev_private;
	struct dc *dc = adev->dm.dc;
	struct dm_crtc_state *dm_crtc_state = to_dm_crtc_state(state);
	int ret = -EINVAL;

	/*
	 * Update interrupt state for the CRTC. This needs to happen whenever
	 * the CRTC has changed or whenever any of its planes have changed.
	 * Atomic check satisfies both of these requirements since the CRTC
	 * is added to the state by DRM during drm_atomic_helper_check_planes.
	 */
	dm_update_crtc_interrupt_state(crtc, state);

	if (unlikely(!dm_crtc_state->stream &&
		     modeset_required(state, NULL, dm_crtc_state->stream))) {
		WARN_ON(1);
		return ret;
	}

	/* In some use cases, like reset, no stream is attached */
	if (!dm_crtc_state->stream)
		return 0;

	/*
	 * We want at least one hardware plane enabled to use
	 * the stream with a cursor enabled.
	 */
	if (state->enable && state->active &&
	    does_crtc_have_active_cursor(state) &&
	    dm_crtc_state->active_planes == 0)
		return -EINVAL;

	if (dc_validate_stream(dc, dm_crtc_state->stream) == DC_OK)
		return 0;

	return ret;
}