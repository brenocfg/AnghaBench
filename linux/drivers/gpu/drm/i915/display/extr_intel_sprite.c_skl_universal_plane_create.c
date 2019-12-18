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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_plane {int pipe; int id; int /*<<< orphan*/  base; scalar_t__ has_ccs; int /*<<< orphan*/  update_slave; int /*<<< orphan*/  check_plane; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; int /*<<< orphan*/  max_stride; int /*<<< orphan*/  frontbuffer_bit; scalar_t__ has_fbc; } ;
struct intel_fbc {int /*<<< orphan*/  possible_framebuffer_bits; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; struct intel_fbc fbc; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int DRM_COLOR_YCBCR_BT601 ; 
 int DRM_COLOR_YCBCR_BT709 ; 
 int DRM_COLOR_YCBCR_FULL_RANGE ; 
 int DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int DRM_MODE_BLEND_COVERAGE ; 
 int DRM_MODE_BLEND_PIXEL_NONE ; 
 int DRM_MODE_BLEND_PREMULTI ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 struct intel_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  INTEL_FRONTBUFFER (int,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_plane*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int PLANE_PRIMARY ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_create_blend_mode_property (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_create_color_properties (int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glk_get_plane_formats (struct drm_i915_private*,int,int,int*) ; 
 int /*<<< orphan*/ * icl_get_plane_formats (struct drm_i915_private*,int,int,int*) ; 
 scalar_t__ icl_is_nv12_y_plane (int) ; 
 int /*<<< orphan*/  icl_update_slave ; 
 struct intel_plane* intel_plane_alloc () ; 
 int /*<<< orphan*/  intel_plane_free (struct intel_plane*) ; 
 int /*<<< orphan*/  intel_plane_helper_funcs ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  skl_disable_plane ; 
 int /*<<< orphan*/ * skl_get_plane_formats (struct drm_i915_private*,int,int,int*) ; 
 int /*<<< orphan*/  skl_plane_check ; 
 int /*<<< orphan*/ * skl_plane_format_modifiers_ccs ; 
 int /*<<< orphan*/ * skl_plane_format_modifiers_noccs ; 
 int /*<<< orphan*/  skl_plane_funcs ; 
 int /*<<< orphan*/  skl_plane_get_hw_state ; 
 scalar_t__ skl_plane_has_ccs (struct drm_i915_private*,int,int) ; 
 scalar_t__ skl_plane_has_fbc (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  skl_plane_max_stride ; 
 int /*<<< orphan*/  skl_update_plane ; 

struct intel_plane *
skl_universal_plane_create(struct drm_i915_private *dev_priv,
			   enum pipe pipe, enum plane_id plane_id)
{
	struct intel_plane *plane;
	enum drm_plane_type plane_type;
	unsigned int supported_rotations;
	unsigned int possible_crtcs;
	const u64 *modifiers;
	const u32 *formats;
	int num_formats;
	int ret;

	plane = intel_plane_alloc();
	if (IS_ERR(plane))
		return plane;

	plane->pipe = pipe;
	plane->id = plane_id;
	plane->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, plane_id);

	plane->has_fbc = skl_plane_has_fbc(dev_priv, pipe, plane_id);
	if (plane->has_fbc) {
		struct intel_fbc *fbc = &dev_priv->fbc;

		fbc->possible_framebuffer_bits |= plane->frontbuffer_bit;
	}

	plane->max_stride = skl_plane_max_stride;
	plane->update_plane = skl_update_plane;
	plane->disable_plane = skl_disable_plane;
	plane->get_hw_state = skl_plane_get_hw_state;
	plane->check_plane = skl_plane_check;
	if (icl_is_nv12_y_plane(plane_id))
		plane->update_slave = icl_update_slave;

	if (INTEL_GEN(dev_priv) >= 11)
		formats = icl_get_plane_formats(dev_priv, pipe,
						plane_id, &num_formats);
	else if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		formats = glk_get_plane_formats(dev_priv, pipe,
						plane_id, &num_formats);
	else
		formats = skl_get_plane_formats(dev_priv, pipe,
						plane_id, &num_formats);

	plane->has_ccs = skl_plane_has_ccs(dev_priv, pipe, plane_id);
	if (plane->has_ccs)
		modifiers = skl_plane_format_modifiers_ccs;
	else
		modifiers = skl_plane_format_modifiers_noccs;

	if (plane_id == PLANE_PRIMARY)
		plane_type = DRM_PLANE_TYPE_PRIMARY;
	else
		plane_type = DRM_PLANE_TYPE_OVERLAY;

	possible_crtcs = BIT(pipe);

	ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
				       possible_crtcs, &skl_plane_funcs,
				       formats, num_formats, modifiers,
				       plane_type,
				       "plane %d%c", plane_id + 1,
				       pipe_name(pipe));
	if (ret)
		goto fail;

	supported_rotations =
		DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
		DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270;

	if (INTEL_GEN(dev_priv) >= 10)
		supported_rotations |= DRM_MODE_REFLECT_X;

	drm_plane_create_rotation_property(&plane->base,
					   DRM_MODE_ROTATE_0,
					   supported_rotations);

	drm_plane_create_color_properties(&plane->base,
					  BIT(DRM_COLOR_YCBCR_BT601) |
					  BIT(DRM_COLOR_YCBCR_BT709),
					  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
					  BIT(DRM_COLOR_YCBCR_FULL_RANGE),
					  DRM_COLOR_YCBCR_BT709,
					  DRM_COLOR_YCBCR_LIMITED_RANGE);

	drm_plane_create_alpha_property(&plane->base);
	drm_plane_create_blend_mode_property(&plane->base,
					     BIT(DRM_MODE_BLEND_PIXEL_NONE) |
					     BIT(DRM_MODE_BLEND_PREMULTI) |
					     BIT(DRM_MODE_BLEND_COVERAGE));

	drm_plane_helper_add(&plane->base, &intel_plane_helper_funcs);

	return plane;

fail:
	intel_plane_free(plane);

	return ERR_PTR(ret);
}