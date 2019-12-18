#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  cntl; int /*<<< orphan*/  base; } ;
struct intel_plane {int pipe; int i9xx_plane; int /*<<< orphan*/  base; TYPE_1__ cursor; int /*<<< orphan*/  check_plane; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; int /*<<< orphan*/  max_stride; int /*<<< orphan*/  id; int /*<<< orphan*/  frontbuffer_bit; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int BIT (int) ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_180 ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_CURSOR ; 
 struct intel_plane* ERR_PTR (int) ; 
 scalar_t__ HAS_CUR_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_FRONTBUFFER (int,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_plane*) ; 
 scalar_t__ IS_I845G (struct drm_i915_private*) ; 
 scalar_t__ IS_I865G (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_CURSOR ; 
 int /*<<< orphan*/  cursor_format_modifiers ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i845_check_cursor ; 
 int /*<<< orphan*/  i845_cursor_get_hw_state ; 
 int /*<<< orphan*/  i845_cursor_max_stride ; 
 int /*<<< orphan*/  i845_disable_cursor ; 
 int /*<<< orphan*/  i845_update_cursor ; 
 int /*<<< orphan*/  i9xx_check_cursor ; 
 int /*<<< orphan*/  i9xx_cursor_get_hw_state ; 
 int /*<<< orphan*/  i9xx_cursor_max_stride ; 
 int /*<<< orphan*/  i9xx_disable_cursor ; 
 int /*<<< orphan*/  i9xx_update_cursor ; 
 int /*<<< orphan*/  intel_cursor_formats ; 
 int /*<<< orphan*/  intel_cursor_plane_funcs ; 
 struct intel_plane* intel_plane_alloc () ; 
 int /*<<< orphan*/  intel_plane_free (struct intel_plane*) ; 
 int /*<<< orphan*/  intel_plane_helper_funcs ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static struct intel_plane *
intel_cursor_plane_create(struct drm_i915_private *dev_priv,
			  enum pipe pipe)
{
	unsigned int possible_crtcs;
	struct intel_plane *cursor;
	int ret;

	cursor = intel_plane_alloc();
	if (IS_ERR(cursor))
		return cursor;

	cursor->pipe = pipe;
	cursor->i9xx_plane = (enum i9xx_plane_id) pipe;
	cursor->id = PLANE_CURSOR;
	cursor->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, cursor->id);

	if (IS_I845G(dev_priv) || IS_I865G(dev_priv)) {
		cursor->max_stride = i845_cursor_max_stride;
		cursor->update_plane = i845_update_cursor;
		cursor->disable_plane = i845_disable_cursor;
		cursor->get_hw_state = i845_cursor_get_hw_state;
		cursor->check_plane = i845_check_cursor;
	} else {
		cursor->max_stride = i9xx_cursor_max_stride;
		cursor->update_plane = i9xx_update_cursor;
		cursor->disable_plane = i9xx_disable_cursor;
		cursor->get_hw_state = i9xx_cursor_get_hw_state;
		cursor->check_plane = i9xx_check_cursor;
	}

	cursor->cursor.base = ~0;
	cursor->cursor.cntl = ~0;

	if (IS_I845G(dev_priv) || IS_I865G(dev_priv) || HAS_CUR_FBC(dev_priv))
		cursor->cursor.size = ~0;

	possible_crtcs = BIT(pipe);

	ret = drm_universal_plane_init(&dev_priv->drm, &cursor->base,
				       possible_crtcs, &intel_cursor_plane_funcs,
				       intel_cursor_formats,
				       ARRAY_SIZE(intel_cursor_formats),
				       cursor_format_modifiers,
				       DRM_PLANE_TYPE_CURSOR,
				       "cursor %c", pipe_name(pipe));
	if (ret)
		goto fail;

	if (INTEL_GEN(dev_priv) >= 4)
		drm_plane_create_rotation_property(&cursor->base,
						   DRM_MODE_ROTATE_0,
						   DRM_MODE_ROTATE_0 |
						   DRM_MODE_ROTATE_180);

	drm_plane_helper_add(&cursor->base, &intel_plane_helper_funcs);

	return cursor;

fail:
	intel_plane_free(cursor);

	return ERR_PTR(ret);
}