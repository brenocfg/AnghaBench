#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {struct TYPE_6__* state; } ;
struct intel_plane_state {int can_scale; int max_downscale; int scaler_id; int pipe; int i9xx_plane; TYPE_1__ base; void* get_hw_state; void* disable_plane; void* update_plane; scalar_t__ has_ccs; int /*<<< orphan*/  check_plane; int /*<<< orphan*/  frontbuffer_bit; scalar_t__ has_fbc; int /*<<< orphan*/  id; } ;
struct intel_plane {int can_scale; int max_downscale; int scaler_id; int pipe; int i9xx_plane; TYPE_1__ base; void* get_hw_state; void* disable_plane; void* update_plane; scalar_t__ has_ccs; int /*<<< orphan*/  check_plane; int /*<<< orphan*/  frontbuffer_bit; scalar_t__ has_fbc; int /*<<< orphan*/  id; } ;
struct intel_fbc {int /*<<< orphan*/  possible_framebuffer_bits; } ;
struct drm_plane_funcs {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; struct intel_fbc fbc; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_FULL_RANGE ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 struct intel_plane_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HAS_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_FRONTBUFFER (int,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int PIPE_B ; 
 int /*<<< orphan*/  PLANE_PRIMARY ; 
 int /*<<< orphan*/  drm_plane_create_color_properties (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,struct drm_plane_funcs const*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct drm_plane_funcs i8xx_plane_funcs ; 
 int /*<<< orphan*/ * i8xx_primary_formats ; 
 struct drm_plane_funcs i965_plane_funcs ; 
 int /*<<< orphan*/ * i965_primary_formats ; 
 void* i9xx_disable_plane ; 
 int /*<<< orphan*/ * i9xx_format_modifiers ; 
 void* i9xx_plane_get_hw_state ; 
 scalar_t__ i9xx_plane_has_fbc (struct drm_i915_private*,int) ; 
 void* i9xx_update_plane ; 
 int /*<<< orphan*/  intel_check_primary_plane ; 
 struct intel_plane_state* intel_create_plane_state (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_plane_helper_funcs ; 
 int /*<<< orphan*/  kfree (struct intel_plane_state*) ; 
 struct intel_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  plane_name (int) ; 
 void* skl_disable_plane ; 
 int /*<<< orphan*/ * skl_format_modifiers_ccs ; 
 int /*<<< orphan*/ * skl_format_modifiers_noccs ; 
 struct drm_plane_funcs skl_plane_funcs ; 
 void* skl_plane_get_hw_state ; 
 scalar_t__ skl_plane_has_ccs (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skl_plane_has_fbc (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skl_plane_has_planar (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skl_pri_planar_formats ; 
 int /*<<< orphan*/ * skl_primary_formats ; 
 void* skl_update_plane ; 

__attribute__((used)) static struct intel_plane *
intel_primary_plane_create(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	struct intel_plane *primary = NULL;
	struct intel_plane_state *state = NULL;
	const struct drm_plane_funcs *plane_funcs;
	const uint32_t *intel_primary_formats;
	unsigned int supported_rotations;
	unsigned int num_formats;
	const uint64_t *modifiers;
	int ret;

	primary = kzalloc(sizeof(*primary), GFP_KERNEL);
	if (!primary) {
		ret = -ENOMEM;
		goto fail;
	}

	state = intel_create_plane_state(&primary->base);
	if (!state) {
		ret = -ENOMEM;
		goto fail;
	}

	primary->base.state = &state->base;

	primary->can_scale = false;
	primary->max_downscale = 1;
	if (INTEL_GEN(dev_priv) >= 9) {
		primary->can_scale = true;
		state->scaler_id = -1;
	}
	primary->pipe = pipe;
	/*
	 * On gen2/3 only plane A can do FBC, but the panel fitter and LVDS
	 * port is hooked to pipe B. Hence we want plane A feeding pipe B.
	 */
	if (HAS_FBC(dev_priv) && INTEL_GEN(dev_priv) < 4)
		primary->i9xx_plane = (enum i9xx_plane_id) !pipe;
	else
		primary->i9xx_plane = (enum i9xx_plane_id) pipe;
	primary->id = PLANE_PRIMARY;
	primary->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, primary->id);

	if (INTEL_GEN(dev_priv) >= 9)
		primary->has_fbc = skl_plane_has_fbc(dev_priv,
						     primary->pipe,
						     primary->id);
	else
		primary->has_fbc = i9xx_plane_has_fbc(dev_priv,
						      primary->i9xx_plane);

	if (primary->has_fbc) {
		struct intel_fbc *fbc = &dev_priv->fbc;

		fbc->possible_framebuffer_bits |= primary->frontbuffer_bit;
	}

	primary->check_plane = intel_check_primary_plane;

	if (INTEL_GEN(dev_priv) >= 9) {
		primary->has_ccs = skl_plane_has_ccs(dev_priv, pipe,
						     PLANE_PRIMARY);

		if (skl_plane_has_planar(dev_priv, pipe, PLANE_PRIMARY)) {
			intel_primary_formats = skl_pri_planar_formats;
			num_formats = ARRAY_SIZE(skl_pri_planar_formats);
		} else {
			intel_primary_formats = skl_primary_formats;
			num_formats = ARRAY_SIZE(skl_primary_formats);
		}

		if (primary->has_ccs)
			modifiers = skl_format_modifiers_ccs;
		else
			modifiers = skl_format_modifiers_noccs;

		primary->update_plane = skl_update_plane;
		primary->disable_plane = skl_disable_plane;
		primary->get_hw_state = skl_plane_get_hw_state;

		plane_funcs = &skl_plane_funcs;
	} else if (INTEL_GEN(dev_priv) >= 4) {
		intel_primary_formats = i965_primary_formats;
		num_formats = ARRAY_SIZE(i965_primary_formats);
		modifiers = i9xx_format_modifiers;

		primary->update_plane = i9xx_update_plane;
		primary->disable_plane = i9xx_disable_plane;
		primary->get_hw_state = i9xx_plane_get_hw_state;

		plane_funcs = &i965_plane_funcs;
	} else {
		intel_primary_formats = i8xx_primary_formats;
		num_formats = ARRAY_SIZE(i8xx_primary_formats);
		modifiers = i9xx_format_modifiers;

		primary->update_plane = i9xx_update_plane;
		primary->disable_plane = i9xx_disable_plane;
		primary->get_hw_state = i9xx_plane_get_hw_state;

		plane_funcs = &i8xx_plane_funcs;
	}

	if (INTEL_GEN(dev_priv) >= 9)
		ret = drm_universal_plane_init(&dev_priv->drm, &primary->base,
					       0, plane_funcs,
					       intel_primary_formats, num_formats,
					       modifiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "plane 1%c", pipe_name(pipe));
	else if (INTEL_GEN(dev_priv) >= 5 || IS_G4X(dev_priv))
		ret = drm_universal_plane_init(&dev_priv->drm, &primary->base,
					       0, plane_funcs,
					       intel_primary_formats, num_formats,
					       modifiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "primary %c", pipe_name(pipe));
	else
		ret = drm_universal_plane_init(&dev_priv->drm, &primary->base,
					       0, plane_funcs,
					       intel_primary_formats, num_formats,
					       modifiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "plane %c",
					       plane_name(primary->i9xx_plane));
	if (ret)
		goto fail;

	if (INTEL_GEN(dev_priv) >= 10) {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
			DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270 |
			DRM_MODE_REFLECT_X;
	} else if (INTEL_GEN(dev_priv) >= 9) {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
			DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270;
	} else if (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
			DRM_MODE_REFLECT_X;
	} else if (INTEL_GEN(dev_priv) >= 4) {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180;
	} else {
		supported_rotations = DRM_MODE_ROTATE_0;
	}

	if (INTEL_GEN(dev_priv) >= 4)
		drm_plane_create_rotation_property(&primary->base,
						   DRM_MODE_ROTATE_0,
						   supported_rotations);

	if (INTEL_GEN(dev_priv) >= 9)
		drm_plane_create_color_properties(&primary->base,
						  BIT(DRM_COLOR_YCBCR_BT601) |
						  BIT(DRM_COLOR_YCBCR_BT709),
						  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
						  BIT(DRM_COLOR_YCBCR_FULL_RANGE),
						  DRM_COLOR_YCBCR_BT709,
						  DRM_COLOR_YCBCR_LIMITED_RANGE);

	drm_plane_helper_add(&primary->base, &intel_plane_helper_funcs);

	return primary;

fail:
	kfree(state);
	kfree(primary);

	return ERR_PTR(ret);
}