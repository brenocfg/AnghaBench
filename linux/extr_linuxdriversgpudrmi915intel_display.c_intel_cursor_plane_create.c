#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  cntl; int /*<<< orphan*/  base; } ;
struct intel_plane_state {int can_scale; int max_downscale; int pipe; int i9xx_plane; int scaler_id; TYPE_2__ base; TYPE_1__ cursor; int /*<<< orphan*/  check_plane; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; int /*<<< orphan*/  id; int /*<<< orphan*/  frontbuffer_bit; } ;
struct intel_plane {int can_scale; int max_downscale; int pipe; int i9xx_plane; int scaler_id; TYPE_2__ base; TYPE_1__ cursor; int /*<<< orphan*/  check_plane; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; int /*<<< orphan*/  id; int /*<<< orphan*/  frontbuffer_bit; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_180 ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_CURSOR ; 
 int ENOMEM ; 
 struct intel_plane_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HAS_CUR_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_FRONTBUFFER (int,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_I845G (struct drm_i915_private*) ; 
 scalar_t__ IS_I865G (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_CURSOR ; 
 int /*<<< orphan*/  cursor_format_modifiers ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i845_check_cursor ; 
 int /*<<< orphan*/  i845_cursor_get_hw_state ; 
 int /*<<< orphan*/  i845_disable_cursor ; 
 int /*<<< orphan*/  i845_update_cursor ; 
 int /*<<< orphan*/  i9xx_check_cursor ; 
 int /*<<< orphan*/  i9xx_cursor_get_hw_state ; 
 int /*<<< orphan*/  i9xx_disable_cursor ; 
 int /*<<< orphan*/  i9xx_update_cursor ; 
 struct intel_plane_state* intel_create_plane_state (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_cursor_formats ; 
 int /*<<< orphan*/  intel_cursor_plane_funcs ; 
 int /*<<< orphan*/  intel_plane_helper_funcs ; 
 int /*<<< orphan*/  kfree (struct intel_plane_state*) ; 
 struct intel_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static struct intel_plane *
intel_cursor_plane_create(struct drm_i915_private *dev_priv,
			  enum pipe pipe)
{
	struct intel_plane *cursor = NULL;
	struct intel_plane_state *state = NULL;
	int ret;

	cursor = kzalloc(sizeof(*cursor), GFP_KERNEL);
	if (!cursor) {
		ret = -ENOMEM;
		goto fail;
	}

	state = intel_create_plane_state(&cursor->base);
	if (!state) {
		ret = -ENOMEM;
		goto fail;
	}

	cursor->base.state = &state->base;

	cursor->can_scale = false;
	cursor->max_downscale = 1;
	cursor->pipe = pipe;
	cursor->i9xx_plane = (enum i9xx_plane_id) pipe;
	cursor->id = PLANE_CURSOR;
	cursor->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, cursor->id);

	if (IS_I845G(dev_priv) || IS_I865G(dev_priv)) {
		cursor->update_plane = i845_update_cursor;
		cursor->disable_plane = i845_disable_cursor;
		cursor->get_hw_state = i845_cursor_get_hw_state;
		cursor->check_plane = i845_check_cursor;
	} else {
		cursor->update_plane = i9xx_update_cursor;
		cursor->disable_plane = i9xx_disable_cursor;
		cursor->get_hw_state = i9xx_cursor_get_hw_state;
		cursor->check_plane = i9xx_check_cursor;
	}

	cursor->cursor.base = ~0;
	cursor->cursor.cntl = ~0;

	if (IS_I845G(dev_priv) || IS_I865G(dev_priv) || HAS_CUR_FBC(dev_priv))
		cursor->cursor.size = ~0;

	ret = drm_universal_plane_init(&dev_priv->drm, &cursor->base,
				       0, &intel_cursor_plane_funcs,
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

	if (INTEL_GEN(dev_priv) >= 9)
		state->scaler_id = -1;

	drm_plane_helper_add(&cursor->base, &intel_plane_helper_funcs);

	return cursor;

fail:
	kfree(state);
	kfree(cursor);

	return ERR_PTR(ret);
}