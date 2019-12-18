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
typedef  int u32 ;
struct drm_framebuffer {int width; int* pitches; TYPE_2__** obj; int /*<<< orphan*/  modifier; TYPE_1__* format; } ;
struct intel_framebuffer {int /*<<< orphan*/  frontbuffer; struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {int flags; int* pitches; scalar_t__* offsets; scalar_t__* handles; int /*<<< orphan*/ * modifier; int /*<<< orphan*/  pixel_format; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_2__ base; } ;
struct drm_format_name_buf {int dummy; } ;
struct TYPE_3__ {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_FORMAT_MOD_LINEAR ; 
 int DRM_MODE_FB_MODIFIERS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I915_FORMAT_MOD_X_TILED ; 
 unsigned int I915_TILING_NONE ; 
 unsigned int I915_TILING_X ; 
 unsigned int I915_TILING_Y ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  drm_any_plane_has_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_framebuffer_init (int /*<<< orphan*/ *,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (int /*<<< orphan*/ *,struct drm_framebuffer*,struct drm_mode_fb_cmd2*) ; 
 unsigned int i915_gem_object_get_stride (struct drm_i915_gem_object*) ; 
 unsigned int i915_gem_object_get_tiling (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_fb_funcs ; 
 int intel_fb_max_stride (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int intel_fb_modifier_to_tiling (int /*<<< orphan*/ ) ; 
 int intel_fb_stride_alignment (struct drm_framebuffer*,int) ; 
 int intel_fill_fb_info (struct drm_i915_private*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  intel_frontbuffer_get (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_frontbuffer_put (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ccs_modifier (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_framebuffer_init(struct intel_framebuffer *intel_fb,
				  struct drm_i915_gem_object *obj,
				  struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct drm_framebuffer *fb = &intel_fb->base;
	u32 max_stride;
	unsigned int tiling, stride;
	int ret = -EINVAL;
	int i;

	intel_fb->frontbuffer = intel_frontbuffer_get(obj);
	if (!intel_fb->frontbuffer)
		return -ENOMEM;

	i915_gem_object_lock(obj);
	tiling = i915_gem_object_get_tiling(obj);
	stride = i915_gem_object_get_stride(obj);
	i915_gem_object_unlock(obj);

	if (mode_cmd->flags & DRM_MODE_FB_MODIFIERS) {
		/*
		 * If there's a fence, enforce that
		 * the fb modifier and tiling mode match.
		 */
		if (tiling != I915_TILING_NONE &&
		    tiling != intel_fb_modifier_to_tiling(mode_cmd->modifier[0])) {
			DRM_DEBUG_KMS("tiling_mode doesn't match fb modifier\n");
			goto err;
		}
	} else {
		if (tiling == I915_TILING_X) {
			mode_cmd->modifier[0] = I915_FORMAT_MOD_X_TILED;
		} else if (tiling == I915_TILING_Y) {
			DRM_DEBUG_KMS("No Y tiling for legacy addfb\n");
			goto err;
		}
	}

	if (!drm_any_plane_has_format(&dev_priv->drm,
				      mode_cmd->pixel_format,
				      mode_cmd->modifier[0])) {
		struct drm_format_name_buf format_name;

		DRM_DEBUG_KMS("unsupported pixel format %s / modifier 0x%llx\n",
			      drm_get_format_name(mode_cmd->pixel_format,
						  &format_name),
			      mode_cmd->modifier[0]);
		goto err;
	}

	/*
	 * gen2/3 display engine uses the fence if present,
	 * so the tiling mode must match the fb modifier exactly.
	 */
	if (INTEL_GEN(dev_priv) < 4 &&
	    tiling != intel_fb_modifier_to_tiling(mode_cmd->modifier[0])) {
		DRM_DEBUG_KMS("tiling_mode must match fb modifier exactly on gen2/3\n");
		goto err;
	}

	max_stride = intel_fb_max_stride(dev_priv, mode_cmd->pixel_format,
					 mode_cmd->modifier[0]);
	if (mode_cmd->pitches[0] > max_stride) {
		DRM_DEBUG_KMS("%s pitch (%u) must be at most %d\n",
			      mode_cmd->modifier[0] != DRM_FORMAT_MOD_LINEAR ?
			      "tiled" : "linear",
			      mode_cmd->pitches[0], max_stride);
		goto err;
	}

	/*
	 * If there's a fence, enforce that
	 * the fb pitch and fence stride match.
	 */
	if (tiling != I915_TILING_NONE && mode_cmd->pitches[0] != stride) {
		DRM_DEBUG_KMS("pitch (%d) must match tiling stride (%d)\n",
			      mode_cmd->pitches[0], stride);
		goto err;
	}

	/* FIXME need to adjust LINOFF/TILEOFF accordingly. */
	if (mode_cmd->offsets[0] != 0)
		goto err;

	drm_helper_mode_fill_fb_struct(&dev_priv->drm, fb, mode_cmd);

	for (i = 0; i < fb->format->num_planes; i++) {
		u32 stride_alignment;

		if (mode_cmd->handles[i] != mode_cmd->handles[0]) {
			DRM_DEBUG_KMS("bad plane %d handle\n", i);
			goto err;
		}

		stride_alignment = intel_fb_stride_alignment(fb, i);

		/*
		 * Display WA #0531: skl,bxt,kbl,glk
		 *
		 * Render decompression and plane width > 3840
		 * combined with horizontal panning requires the
		 * plane stride to be a multiple of 4. We'll just
		 * require the entire fb to accommodate that to avoid
		 * potential runtime errors at plane configuration time.
		 */
		if (IS_GEN(dev_priv, 9) && i == 0 && fb->width > 3840 &&
		    is_ccs_modifier(fb->modifier))
			stride_alignment *= 4;

		if (fb->pitches[i] & (stride_alignment - 1)) {
			DRM_DEBUG_KMS("plane %d pitch (%d) must be at least %u byte aligned\n",
				      i, fb->pitches[i], stride_alignment);
			goto err;
		}

		fb->obj[i] = &obj->base;
	}

	ret = intel_fill_fb_info(dev_priv, fb);
	if (ret)
		goto err;

	ret = drm_framebuffer_init(&dev_priv->drm, fb, &intel_fb_funcs);
	if (ret) {
		DRM_ERROR("framebuffer init failed %d\n", ret);
		goto err;
	}

	return 0;

err:
	intel_frontbuffer_put(intel_fb->frontbuffer);
	return ret;
}