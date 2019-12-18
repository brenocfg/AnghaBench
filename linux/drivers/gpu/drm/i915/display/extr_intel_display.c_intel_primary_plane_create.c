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
struct intel_plane {int pipe; int i9xx_plane; int /*<<< orphan*/  base; void* check_plane; void* get_hw_state; void* disable_plane; void* update_plane; void* max_stride; int /*<<< orphan*/  frontbuffer_bit; scalar_t__ has_fbc; int /*<<< orphan*/  id; } ;
struct intel_fbc {int /*<<< orphan*/  possible_framebuffer_bits; } ;
struct drm_plane_funcs {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; struct intel_fbc fbc; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int BIT (int) ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 struct intel_plane* ERR_PTR (int) ; 
 scalar_t__ HAS_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_FRONTBUFFER (int,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_plane*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int PIPE_B ; 
 int /*<<< orphan*/  PLANE_PRIMARY ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,struct drm_plane_funcs const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct drm_plane_funcs i8xx_plane_funcs ; 
 int /*<<< orphan*/ * i8xx_primary_formats ; 
 struct drm_plane_funcs i965_plane_funcs ; 
 int /*<<< orphan*/ * i965_primary_formats ; 
 void* i9xx_disable_plane ; 
 int /*<<< orphan*/ * i9xx_format_modifiers ; 
 void* i9xx_plane_check ; 
 void* i9xx_plane_get_hw_state ; 
 scalar_t__ i9xx_plane_has_fbc (struct drm_i915_private*,int) ; 
 void* i9xx_plane_max_stride ; 
 void* i9xx_update_plane ; 
 struct intel_plane* intel_plane_alloc () ; 
 int /*<<< orphan*/  intel_plane_free (struct intel_plane*) ; 
 int /*<<< orphan*/  intel_plane_helper_funcs ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  plane_name (int) ; 
 struct intel_plane* skl_universal_plane_create (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_plane *
intel_primary_plane_create(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	struct intel_plane *plane;
	const struct drm_plane_funcs *plane_funcs;
	unsigned int supported_rotations;
	unsigned int possible_crtcs;
	const u64 *modifiers;
	const u32 *formats;
	int num_formats;
	int ret;

	if (INTEL_GEN(dev_priv) >= 9)
		return skl_universal_plane_create(dev_priv, pipe,
						  PLANE_PRIMARY);

	plane = intel_plane_alloc();
	if (IS_ERR(plane))
		return plane;

	plane->pipe = pipe;
	/*
	 * On gen2/3 only plane A can do FBC, but the panel fitter and LVDS
	 * port is hooked to pipe B. Hence we want plane A feeding pipe B.
	 */
	if (HAS_FBC(dev_priv) && INTEL_GEN(dev_priv) < 4)
		plane->i9xx_plane = (enum i9xx_plane_id) !pipe;
	else
		plane->i9xx_plane = (enum i9xx_plane_id) pipe;
	plane->id = PLANE_PRIMARY;
	plane->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, plane->id);

	plane->has_fbc = i9xx_plane_has_fbc(dev_priv, plane->i9xx_plane);
	if (plane->has_fbc) {
		struct intel_fbc *fbc = &dev_priv->fbc;

		fbc->possible_framebuffer_bits |= plane->frontbuffer_bit;
	}

	if (INTEL_GEN(dev_priv) >= 4) {
		formats = i965_primary_formats;
		num_formats = ARRAY_SIZE(i965_primary_formats);
		modifiers = i9xx_format_modifiers;

		plane->max_stride = i9xx_plane_max_stride;
		plane->update_plane = i9xx_update_plane;
		plane->disable_plane = i9xx_disable_plane;
		plane->get_hw_state = i9xx_plane_get_hw_state;
		plane->check_plane = i9xx_plane_check;

		plane_funcs = &i965_plane_funcs;
	} else {
		formats = i8xx_primary_formats;
		num_formats = ARRAY_SIZE(i8xx_primary_formats);
		modifiers = i9xx_format_modifiers;

		plane->max_stride = i9xx_plane_max_stride;
		plane->update_plane = i9xx_update_plane;
		plane->disable_plane = i9xx_disable_plane;
		plane->get_hw_state = i9xx_plane_get_hw_state;
		plane->check_plane = i9xx_plane_check;

		plane_funcs = &i8xx_plane_funcs;
	}

	possible_crtcs = BIT(pipe);

	if (INTEL_GEN(dev_priv) >= 5 || IS_G4X(dev_priv))
		ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
					       possible_crtcs, plane_funcs,
					       formats, num_formats, modifiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "primary %c", pipe_name(pipe));
	else
		ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
					       possible_crtcs, plane_funcs,
					       formats, num_formats, modifiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "plane %c",
					       plane_name(plane->i9xx_plane));
	if (ret)
		goto fail;

	if (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) {
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
		drm_plane_create_rotation_property(&plane->base,
						   DRM_MODE_ROTATE_0,
						   supported_rotations);

	drm_plane_helper_add(&plane->base, &intel_plane_helper_funcs);

	return plane;

fail:
	intel_plane_free(plane);

	return ERR_PTR(ret);
}