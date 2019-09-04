#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_initial_plane_config {scalar_t__ base; scalar_t__ size; int tiling; TYPE_2__* fb; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_mode_fb_cmd2 {int* pitches; int /*<<< orphan*/  flags; int /*<<< orphan*/ * modifier; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  member_0; } ;
struct drm_i915_private {int stolen_usable_size; } ;
struct drm_i915_gem_object {int tiling_and_stride; } ;
struct drm_framebuffer {int* pitches; int /*<<< orphan*/  modifier; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__* format; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  format; } ;
struct TYPE_5__ {struct drm_framebuffer base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_FB_MODIFIERS ; 
 int I915_TILING_X ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct drm_i915_gem_object* i915_gem_object_create_stolen_for_preallocated (struct drm_i915_private*,int,int,int) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 scalar_t__ intel_framebuffer_init (int /*<<< orphan*/ ,struct drm_i915_gem_object*,struct drm_mode_fb_cmd2*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 int round_up (scalar_t__,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static bool
intel_alloc_initial_plane_obj(struct intel_crtc *crtc,
			      struct intel_initial_plane_config *plane_config)
{
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_gem_object *obj = NULL;
	struct drm_mode_fb_cmd2 mode_cmd = { 0 };
	struct drm_framebuffer *fb = &plane_config->fb->base;
	u32 base_aligned = round_down(plane_config->base, PAGE_SIZE);
	u32 size_aligned = round_up(plane_config->base + plane_config->size,
				    PAGE_SIZE);

	size_aligned -= base_aligned;

	if (plane_config->size == 0)
		return false;

	/* If the FB is too big, just don't use it since fbdev is not very
	 * important and we should probably use that space with FBC or other
	 * features. */
	if (size_aligned * 2 > dev_priv->stolen_usable_size)
		return false;

	mutex_lock(&dev->struct_mutex);
	obj = i915_gem_object_create_stolen_for_preallocated(dev_priv,
							     base_aligned,
							     base_aligned,
							     size_aligned);
	mutex_unlock(&dev->struct_mutex);
	if (!obj)
		return false;

	if (plane_config->tiling == I915_TILING_X)
		obj->tiling_and_stride = fb->pitches[0] | I915_TILING_X;

	mode_cmd.pixel_format = fb->format->format;
	mode_cmd.width = fb->width;
	mode_cmd.height = fb->height;
	mode_cmd.pitches[0] = fb->pitches[0];
	mode_cmd.modifier[0] = fb->modifier;
	mode_cmd.flags = DRM_MODE_FB_MODIFIERS;

	if (intel_framebuffer_init(to_intel_framebuffer(fb), obj, &mode_cmd)) {
		DRM_DEBUG_KMS("intel fb init failed\n");
		goto out_unref_obj;
	}


	DRM_DEBUG_KMS("initial plane fb obj %p\n", obj);
	return true;

out_unref_obj:
	i915_gem_object_put(obj);
	return false;
}