#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int rotation; int crtc_h; int crtc_w; struct drm_framebuffer* fb; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_5__ base; TYPE_4__* color_plane; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {TYPE_3__* phys_handle; } ;
struct drm_framebuffer {TYPE_6__* format; } ;
struct TYPE_9__ {scalar_t__ cursor_needs_physical; } ;
struct TYPE_14__ {TYPE_2__ display; } ;
struct TYPE_13__ {int* cpp; } ;
struct TYPE_11__ {scalar_t__ offset; } ;
struct TYPE_10__ {int busaddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_ROTATE_180 ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 TYPE_7__* INTEL_INFO (struct drm_i915_private*) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer const*) ; 
 int intel_plane_ggtt_offset (struct intel_plane_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 intel_cursor_base(const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	const struct drm_i915_gem_object *obj = intel_fb_obj(fb);
	u32 base;

	if (INTEL_INFO(dev_priv)->display.cursor_needs_physical)
		base = obj->phys_handle->busaddr;
	else
		base = intel_plane_ggtt_offset(plane_state);

	base += plane_state->color_plane[0].offset;

	/* ILK+ do this automagically */
	if (HAS_GMCH(dev_priv) &&
	    plane_state->base.rotation & DRM_MODE_ROTATE_180)
		base += (plane_state->base.crtc_h *
			 plane_state->base.crtc_w - 1) * fb->format->cpp[0];

	return base;
}