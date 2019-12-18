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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_plane {int /*<<< orphan*/  (* max_stride ) (struct intel_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  primary; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  PIPE_A ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

u32 intel_plane_fb_max_stride(struct drm_i915_private *dev_priv,
			      u32 pixel_format, u64 modifier)
{
	struct intel_crtc *crtc;
	struct intel_plane *plane;

	/*
	 * We assume the primary plane for pipe A has
	 * the highest stride limits of them all.
	 */
	crtc = intel_get_crtc_for_pipe(dev_priv, PIPE_A);
	plane = to_intel_plane(crtc->base.primary);

	return plane->max_stride(plane, pixel_format, modifier,
				 DRM_MODE_ROTATE_0);
}