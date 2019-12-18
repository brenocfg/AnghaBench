#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct drm_plane* plane; int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_encoding; int /*<<< orphan*/  zpos; int /*<<< orphan*/  alpha; int /*<<< orphan*/  pixel_blend_mode; int /*<<< orphan*/  rotation; } ;
struct komeda_plane_state {TYPE_3__ base; } ;
struct komeda_plane {TYPE_2__* layer; } ;
struct drm_plane {TYPE_3__* state; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PREMULTI ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 struct komeda_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct komeda_plane* to_kplane (struct drm_plane*) ; 

__attribute__((used)) static void komeda_plane_reset(struct drm_plane *plane)
{
	struct komeda_plane_state *state;
	struct komeda_plane *kplane = to_kplane(plane);

	if (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);

	kfree(plane->state);
	plane->state = NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state) {
		state->base.rotation = DRM_MODE_ROTATE_0;
		state->base.pixel_blend_mode = DRM_MODE_BLEND_PREMULTI;
		state->base.alpha = DRM_BLEND_ALPHA_OPAQUE;
		state->base.zpos = kplane->layer->base.id;
		state->base.color_encoding = DRM_COLOR_YCBCR_BT601;
		state->base.color_range = DRM_COLOR_YCBCR_LIMITED_RANGE;
		plane->state = &state->base;
		plane->state->plane = plane;
	}
}