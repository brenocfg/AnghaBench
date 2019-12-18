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
struct intel_vgpu_fb_info {int drm_format_mod; unsigned int stride; int /*<<< orphan*/  size; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {unsigned int tiling_and_stride; scalar_t__ write_domain; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
#define  DRM_FORMAT_MOD_LINEAR 131 
#define  I915_FORMAT_MOD_X_TILED 130 
#define  I915_FORMAT_MOD_Y_TILED 129 
#define  I915_FORMAT_MOD_Yf_TILED 128 
 int /*<<< orphan*/  I915_GEM_DOMAIN_GTT ; 
 unsigned int I915_TILING_NONE ; 
 void* I915_TILING_X ; 
 unsigned int I915_TILING_Y ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  drm_gem_private_object_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int) ; 
 struct drm_i915_gem_object* i915_gem_object_alloc () ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_vgpu_gem_ops ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static struct drm_i915_gem_object *vgpu_create_gem(struct drm_device *dev,
		struct intel_vgpu_fb_info *info)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_gem_object *obj;

	obj = i915_gem_object_alloc();
	if (obj == NULL)
		return NULL;

	drm_gem_private_object_init(dev, &obj->base,
		roundup(info->size, PAGE_SIZE));
	i915_gem_object_init(obj, &intel_vgpu_gem_ops);

	obj->read_domains = I915_GEM_DOMAIN_GTT;
	obj->write_domain = 0;
	if (INTEL_GEN(dev_priv) >= 9) {
		unsigned int tiling_mode = 0;
		unsigned int stride = 0;

		switch (info->drm_format_mod) {
		case DRM_FORMAT_MOD_LINEAR:
			tiling_mode = I915_TILING_NONE;
			break;
		case I915_FORMAT_MOD_X_TILED:
			tiling_mode = I915_TILING_X;
			stride = info->stride;
			break;
		case I915_FORMAT_MOD_Y_TILED:
		case I915_FORMAT_MOD_Yf_TILED:
			tiling_mode = I915_TILING_Y;
			stride = info->stride;
			break;
		default:
			gvt_dbg_core("invalid drm_format_mod %llx for tiling\n",
				     info->drm_format_mod);
		}
		obj->tiling_and_stride = tiling_mode | stride;
	} else {
		obj->tiling_and_stride = info->drm_format_mod ?
					I915_TILING_X : 0;
	}

	return obj;
}