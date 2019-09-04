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
struct intel_plane_state {int can_scale; int scaler_id; int max_downscale; int pipe; int i9xx_plane; TYPE_1__ base; int /*<<< orphan*/  check_plane; scalar_t__ id; int /*<<< orphan*/  frontbuffer_bit; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; scalar_t__ has_ccs; } ;
struct intel_plane {int can_scale; int scaler_id; int max_downscale; int pipe; int i9xx_plane; TYPE_1__ base; int /*<<< orphan*/  check_plane; scalar_t__ id; int /*<<< orphan*/  frontbuffer_bit; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; scalar_t__ has_ccs; } ;
struct drm_plane_funcs {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int ENOMEM ; 
 struct intel_plane_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_FRONTBUFFER (int,scalar_t__) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int PIPE_B ; 
 scalar_t__ PLANE_SPRITE0 ; 
 int /*<<< orphan*/  drm_plane_create_color_properties (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ *,TYPE_1__*,unsigned long,struct drm_plane_funcs const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  g4x_disable_plane ; 
 int /*<<< orphan*/ * g4x_plane_formats ; 
 int /*<<< orphan*/  g4x_plane_get_hw_state ; 
 struct drm_plane_funcs g4x_sprite_funcs ; 
 int /*<<< orphan*/  g4x_update_plane ; 
 int /*<<< orphan*/ * i9xx_plane_format_modifiers ; 
 int /*<<< orphan*/  intel_check_sprite_plane ; 
 struct intel_plane_state* intel_create_plane_state (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_plane_helper_funcs ; 
 int /*<<< orphan*/  ivb_disable_plane ; 
 int /*<<< orphan*/  ivb_plane_get_hw_state ; 
 int /*<<< orphan*/  ivb_update_plane ; 
 int /*<<< orphan*/  kfree (struct intel_plane_state*) ; 
 struct intel_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  skl_disable_plane ; 
 int /*<<< orphan*/ * skl_planar_formats ; 
 int /*<<< orphan*/ * skl_plane_format_modifiers_ccs ; 
 int /*<<< orphan*/ * skl_plane_format_modifiers_noccs ; 
 int /*<<< orphan*/ * skl_plane_formats ; 
 struct drm_plane_funcs skl_plane_funcs ; 
 int /*<<< orphan*/  skl_plane_get_hw_state ; 
 scalar_t__ skl_plane_has_ccs (struct drm_i915_private*,int,scalar_t__) ; 
 scalar_t__ skl_plane_has_planar (struct drm_i915_private*,int,scalar_t__) ; 
 int /*<<< orphan*/  skl_update_plane ; 
 int /*<<< orphan*/ * snb_plane_formats ; 
 struct drm_plane_funcs snb_sprite_funcs ; 
 int /*<<< orphan*/  sprite_name (int,int) ; 
 int /*<<< orphan*/  vlv_disable_plane ; 
 int /*<<< orphan*/ * vlv_plane_formats ; 
 int /*<<< orphan*/  vlv_plane_get_hw_state ; 
 struct drm_plane_funcs vlv_sprite_funcs ; 
 int /*<<< orphan*/  vlv_update_plane ; 

struct intel_plane *
intel_sprite_plane_create(struct drm_i915_private *dev_priv,
			  enum pipe pipe, int plane)
{
	struct intel_plane *intel_plane = NULL;
	struct intel_plane_state *state = NULL;
	const struct drm_plane_funcs *plane_funcs;
	unsigned long possible_crtcs;
	const uint32_t *plane_formats;
	const uint64_t *modifiers;
	unsigned int supported_rotations;
	int num_plane_formats;
	int ret;

	intel_plane = kzalloc(sizeof(*intel_plane), GFP_KERNEL);
	if (!intel_plane) {
		ret = -ENOMEM;
		goto fail;
	}

	state = intel_create_plane_state(&intel_plane->base);
	if (!state) {
		ret = -ENOMEM;
		goto fail;
	}
	intel_plane->base.state = &state->base;

	if (INTEL_GEN(dev_priv) >= 9) {
		intel_plane->can_scale = true;
		state->scaler_id = -1;

		intel_plane->has_ccs = skl_plane_has_ccs(dev_priv, pipe,
							 PLANE_SPRITE0 + plane);

		intel_plane->update_plane = skl_update_plane;
		intel_plane->disable_plane = skl_disable_plane;
		intel_plane->get_hw_state = skl_plane_get_hw_state;

		if (skl_plane_has_planar(dev_priv, pipe,
					 PLANE_SPRITE0 + plane)) {
			plane_formats = skl_planar_formats;
			num_plane_formats = ARRAY_SIZE(skl_planar_formats);
		} else {
			plane_formats = skl_plane_formats;
			num_plane_formats = ARRAY_SIZE(skl_plane_formats);
		}

		if (intel_plane->has_ccs)
			modifiers = skl_plane_format_modifiers_ccs;
		else
			modifiers = skl_plane_format_modifiers_noccs;

		plane_funcs = &skl_plane_funcs;
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		intel_plane->can_scale = false;
		intel_plane->max_downscale = 1;

		intel_plane->update_plane = vlv_update_plane;
		intel_plane->disable_plane = vlv_disable_plane;
		intel_plane->get_hw_state = vlv_plane_get_hw_state;

		plane_formats = vlv_plane_formats;
		num_plane_formats = ARRAY_SIZE(vlv_plane_formats);
		modifiers = i9xx_plane_format_modifiers;

		plane_funcs = &vlv_sprite_funcs;
	} else if (INTEL_GEN(dev_priv) >= 7) {
		if (IS_IVYBRIDGE(dev_priv)) {
			intel_plane->can_scale = true;
			intel_plane->max_downscale = 2;
		} else {
			intel_plane->can_scale = false;
			intel_plane->max_downscale = 1;
		}

		intel_plane->update_plane = ivb_update_plane;
		intel_plane->disable_plane = ivb_disable_plane;
		intel_plane->get_hw_state = ivb_plane_get_hw_state;

		plane_formats = snb_plane_formats;
		num_plane_formats = ARRAY_SIZE(snb_plane_formats);
		modifiers = i9xx_plane_format_modifiers;

		plane_funcs = &snb_sprite_funcs;
	} else {
		intel_plane->can_scale = true;
		intel_plane->max_downscale = 16;

		intel_plane->update_plane = g4x_update_plane;
		intel_plane->disable_plane = g4x_disable_plane;
		intel_plane->get_hw_state = g4x_plane_get_hw_state;

		modifiers = i9xx_plane_format_modifiers;
		if (IS_GEN6(dev_priv)) {
			plane_formats = snb_plane_formats;
			num_plane_formats = ARRAY_SIZE(snb_plane_formats);

			plane_funcs = &snb_sprite_funcs;
		} else {
			plane_formats = g4x_plane_formats;
			num_plane_formats = ARRAY_SIZE(g4x_plane_formats);

			plane_funcs = &g4x_sprite_funcs;
		}
	}

	if (INTEL_GEN(dev_priv) >= 9) {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
			DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270;
	} else if (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
			DRM_MODE_REFLECT_X;
	} else {
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180;
	}

	intel_plane->pipe = pipe;
	intel_plane->i9xx_plane = plane;
	intel_plane->id = PLANE_SPRITE0 + plane;
	intel_plane->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, intel_plane->id);
	intel_plane->check_plane = intel_check_sprite_plane;

	possible_crtcs = (1 << pipe);

	if (INTEL_GEN(dev_priv) >= 9)
		ret = drm_universal_plane_init(&dev_priv->drm, &intel_plane->base,
					       possible_crtcs, plane_funcs,
					       plane_formats, num_plane_formats,
					       modifiers,
					       DRM_PLANE_TYPE_OVERLAY,
					       "plane %d%c", plane + 2, pipe_name(pipe));
	else
		ret = drm_universal_plane_init(&dev_priv->drm, &intel_plane->base,
					       possible_crtcs, plane_funcs,
					       plane_formats, num_plane_formats,
					       modifiers,
					       DRM_PLANE_TYPE_OVERLAY,
					       "sprite %c", sprite_name(pipe, plane));
	if (ret)
		goto fail;

	drm_plane_create_rotation_property(&intel_plane->base,
					   DRM_MODE_ROTATE_0,
					   supported_rotations);

	drm_plane_create_color_properties(&intel_plane->base,
					  BIT(DRM_COLOR_YCBCR_BT601) |
					  BIT(DRM_COLOR_YCBCR_BT709),
					  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
					  BIT(DRM_COLOR_YCBCR_FULL_RANGE),
					  DRM_COLOR_YCBCR_BT709,
					  DRM_COLOR_YCBCR_LIMITED_RANGE);

	drm_plane_helper_add(&intel_plane->base, &intel_plane_helper_funcs);

	return intel_plane;

fail:
	kfree(state);
	kfree(intel_plane);

	return ERR_PTR(ret);
}