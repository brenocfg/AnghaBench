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
struct drm_framebuffer {int width; int height; int const modifier; int* pitches; TYPE_2__** obj; TYPE_1__* format; } ;
struct intel_framebuffer {struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {int flags; int* modifier; int* pitches; scalar_t__* offsets; scalar_t__* handles; int /*<<< orphan*/  pixel_format; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  framebuffer_references; TYPE_2__ base; } ;
struct drm_format_name_buf {int dummy; } ;
struct TYPE_3__ {int const format; int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
#define  DRM_FORMAT_ABGR2101010 148 
#define  DRM_FORMAT_ABGR8888 147 
#define  DRM_FORMAT_ARGB8888 146 
#define  DRM_FORMAT_C8 145 
#define  DRM_FORMAT_MOD_LINEAR 144 
#define  DRM_FORMAT_NV12 143 
#define  DRM_FORMAT_RGB565 142 
#define  DRM_FORMAT_UYVY 141 
#define  DRM_FORMAT_VYUY 140 
#define  DRM_FORMAT_XBGR2101010 139 
#define  DRM_FORMAT_XBGR8888 138 
#define  DRM_FORMAT_XRGB1555 137 
#define  DRM_FORMAT_XRGB2101010 136 
#define  DRM_FORMAT_XRGB8888 135 
#define  DRM_FORMAT_YUYV 134 
#define  DRM_FORMAT_YVYU 133 
 int DRM_MODE_FB_MODIFIERS ; 
 int EINVAL ; 
#define  I915_FORMAT_MOD_X_TILED 132 
#define  I915_FORMAT_MOD_Y_TILED 131 
#define  I915_FORMAT_MOD_Y_TILED_CCS 130 
#define  I915_FORMAT_MOD_Yf_TILED 129 
#define  I915_FORMAT_MOD_Yf_TILED_CCS 128 
 unsigned int I915_TILING_NONE ; 
 unsigned int I915_TILING_X ; 
 unsigned int I915_TILING_Y ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_BROXTON (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int SKL_MIN_YUV_420_SRC_H ; 
 int SKL_MIN_YUV_420_SRC_W ; 
 int drm_framebuffer_init (int /*<<< orphan*/ *,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (int /*<<< orphan*/ *,struct drm_framebuffer*,struct drm_mode_fb_cmd2*) ; 
 unsigned int i915_gem_object_get_stride (struct drm_i915_gem_object*) ; 
 unsigned int i915_gem_object_get_tiling (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_fb_funcs ; 
 unsigned int intel_fb_modifier_to_tiling (int) ; 
 int intel_fb_pitch_limit (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int intel_fb_stride_alignment (struct drm_framebuffer*,int) ; 
 int intel_fill_fb_info (struct drm_i915_private*,struct drm_framebuffer*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_framebuffer_init(struct intel_framebuffer *intel_fb,
				  struct drm_i915_gem_object *obj,
				  struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct drm_framebuffer *fb = &intel_fb->base;
	struct drm_format_name_buf format_name;
	u32 pitch_limit;
	unsigned int tiling, stride;
	int ret = -EINVAL;
	int i;

	i915_gem_object_lock(obj);
	obj->framebuffer_references++;
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

	/* Passed in modifier sanity checking. */
	switch (mode_cmd->modifier[0]) {
	case I915_FORMAT_MOD_Y_TILED_CCS:
	case I915_FORMAT_MOD_Yf_TILED_CCS:
		switch (mode_cmd->pixel_format) {
		case DRM_FORMAT_XBGR8888:
		case DRM_FORMAT_ABGR8888:
		case DRM_FORMAT_XRGB8888:
		case DRM_FORMAT_ARGB8888:
			break;
		default:
			DRM_DEBUG_KMS("RC supported only with RGB8888 formats\n");
			goto err;
		}
		/* fall through */
	case I915_FORMAT_MOD_Y_TILED:
	case I915_FORMAT_MOD_Yf_TILED:
		if (INTEL_GEN(dev_priv) < 9) {
			DRM_DEBUG_KMS("Unsupported tiling 0x%llx!\n",
				      mode_cmd->modifier[0]);
			goto err;
		}
	case DRM_FORMAT_MOD_LINEAR:
	case I915_FORMAT_MOD_X_TILED:
		break;
	default:
		DRM_DEBUG_KMS("Unsupported fb modifier 0x%llx!\n",
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

	pitch_limit = intel_fb_pitch_limit(dev_priv, mode_cmd->modifier[0],
					   mode_cmd->pixel_format);
	if (mode_cmd->pitches[0] > pitch_limit) {
		DRM_DEBUG_KMS("%s pitch (%u) must be at most %d\n",
			      mode_cmd->modifier[0] != DRM_FORMAT_MOD_LINEAR ?
			      "tiled" : "linear",
			      mode_cmd->pitches[0], pitch_limit);
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

	/* Reject formats not supported by any plane early. */
	switch (mode_cmd->pixel_format) {
	case DRM_FORMAT_C8:
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		break;
	case DRM_FORMAT_XRGB1555:
		if (INTEL_GEN(dev_priv) > 3) {
			DRM_DEBUG_KMS("unsupported pixel format: %s\n",
				      drm_get_format_name(mode_cmd->pixel_format, &format_name));
			goto err;
		}
		break;
	case DRM_FORMAT_ABGR8888:
		if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv) &&
		    INTEL_GEN(dev_priv) < 9) {
			DRM_DEBUG_KMS("unsupported pixel format: %s\n",
				      drm_get_format_name(mode_cmd->pixel_format, &format_name));
			goto err;
		}
		break;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_XBGR2101010:
		if (INTEL_GEN(dev_priv) < 4) {
			DRM_DEBUG_KMS("unsupported pixel format: %s\n",
				      drm_get_format_name(mode_cmd->pixel_format, &format_name));
			goto err;
		}
		break;
	case DRM_FORMAT_ABGR2101010:
		if (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv)) {
			DRM_DEBUG_KMS("unsupported pixel format: %s\n",
				      drm_get_format_name(mode_cmd->pixel_format, &format_name));
			goto err;
		}
		break;
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_VYUY:
		if (INTEL_GEN(dev_priv) < 5 && !IS_G4X(dev_priv)) {
			DRM_DEBUG_KMS("unsupported pixel format: %s\n",
				      drm_get_format_name(mode_cmd->pixel_format, &format_name));
			goto err;
		}
		break;
	case DRM_FORMAT_NV12:
		if (INTEL_GEN(dev_priv) < 9 || IS_SKYLAKE(dev_priv) ||
		    IS_BROXTON(dev_priv)) {
			DRM_DEBUG_KMS("unsupported pixel format: %s\n",
				      drm_get_format_name(mode_cmd->pixel_format,
							  &format_name));
			goto err;
		}
		break;
	default:
		DRM_DEBUG_KMS("unsupported pixel format: %s\n",
			      drm_get_format_name(mode_cmd->pixel_format, &format_name));
		goto err;
	}

	/* FIXME need to adjust LINOFF/TILEOFF accordingly. */
	if (mode_cmd->offsets[0] != 0)
		goto err;

	drm_helper_mode_fill_fb_struct(&dev_priv->drm, fb, mode_cmd);

	if (fb->format->format == DRM_FORMAT_NV12 &&
	    (fb->width < SKL_MIN_YUV_420_SRC_W ||
	     fb->height < SKL_MIN_YUV_420_SRC_H ||
	     (fb->width % 4) != 0 || (fb->height % 4) != 0)) {
		DRM_DEBUG_KMS("src dimensions not correct for NV12\n");
		goto err;
	}

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
		if (IS_GEN9(dev_priv) && i == 0 && fb->width > 3840 &&
		    (fb->modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
		     fb->modifier == I915_FORMAT_MOD_Yf_TILED_CCS))
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
	i915_gem_object_lock(obj);
	obj->framebuffer_references--;
	i915_gem_object_unlock(obj);
	return ret;
}