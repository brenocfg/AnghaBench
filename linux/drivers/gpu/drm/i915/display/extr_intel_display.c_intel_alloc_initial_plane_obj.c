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
struct drm_mode_fb_cmd2 {int* pitches; int* modifier; int /*<<< orphan*/  flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  member_0; } ;
struct drm_i915_private {int stolen_usable_size; } ;
struct drm_i915_gem_object {int tiling_and_stride; } ;
struct drm_framebuffer {int modifier; int* pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__* format; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  format; } ;
struct TYPE_5__ {struct drm_framebuffer base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
#define  DRM_FORMAT_MOD_LINEAR 133 
 int /*<<< orphan*/  DRM_MODE_FB_MODIFIERS ; 
#define  I915_FORMAT_MOD_X_TILED 132 
#define  I915_FORMAT_MOD_Y_TILED 131 
#define  I915_TILING_NONE 130 
#define  I915_TILING_X 129 
#define  I915_TILING_Y 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
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
	struct drm_mode_fb_cmd2 mode_cmd = { 0 };
	struct drm_framebuffer *fb = &plane_config->fb->base;
	u32 base_aligned = round_down(plane_config->base, PAGE_SIZE);
	u32 size_aligned = round_up(plane_config->base + plane_config->size,
				    PAGE_SIZE);
	struct drm_i915_gem_object *obj;
	bool ret = false;

	size_aligned -= base_aligned;

	if (plane_config->size == 0)
		return false;

	/* If the FB is too big, just don't use it since fbdev is not very
	 * important and we should probably use that space with FBC or other
	 * features. */
	if (size_aligned * 2 > dev_priv->stolen_usable_size)
		return false;

	switch (fb->modifier) {
	case DRM_FORMAT_MOD_LINEAR:
	case I915_FORMAT_MOD_X_TILED:
	case I915_FORMAT_MOD_Y_TILED:
		break;
	default:
		DRM_DEBUG_DRIVER("Unsupported modifier for initial FB: 0x%llx\n",
				 fb->modifier);
		return false;
	}

	mutex_lock(&dev->struct_mutex);
	obj = i915_gem_object_create_stolen_for_preallocated(dev_priv,
							     base_aligned,
							     base_aligned,
							     size_aligned);
	mutex_unlock(&dev->struct_mutex);
	if (!obj)
		return false;

	switch (plane_config->tiling) {
	case I915_TILING_NONE:
		break;
	case I915_TILING_X:
	case I915_TILING_Y:
		obj->tiling_and_stride = fb->pitches[0] | plane_config->tiling;
		break;
	default:
		MISSING_CASE(plane_config->tiling);
		goto out;
	}

	mode_cmd.pixel_format = fb->format->format;
	mode_cmd.width = fb->width;
	mode_cmd.height = fb->height;
	mode_cmd.pitches[0] = fb->pitches[0];
	mode_cmd.modifier[0] = fb->modifier;
	mode_cmd.flags = DRM_MODE_FB_MODIFIERS;

	if (intel_framebuffer_init(to_intel_framebuffer(fb), obj, &mode_cmd)) {
		DRM_DEBUG_KMS("intel fb init failed\n");
		goto out;
	}


	DRM_DEBUG_KMS("initial plane fb obj %p\n", obj);
	ret = true;
out:
	i915_gem_object_put(obj);
	return ret;
}