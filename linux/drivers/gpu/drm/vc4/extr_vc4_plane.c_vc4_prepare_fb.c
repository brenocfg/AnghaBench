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
struct vc4_bo {int dummy; } ;
struct drm_plane_state {scalar_t__ fb; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {scalar_t__ fb; } ;

/* Variables and functions */
 TYPE_2__* drm_fb_cma_get_gem_obj (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_fb_prepare_fb (struct drm_plane*,struct drm_plane_state*) ; 
 struct vc4_bo* to_vc4_bo (int /*<<< orphan*/ *) ; 
 int vc4_bo_inc_usecnt (struct vc4_bo*) ; 

__attribute__((used)) static int vc4_prepare_fb(struct drm_plane *plane,
			  struct drm_plane_state *state)
{
	struct vc4_bo *bo;
	int ret;

	if (!state->fb)
		return 0;

	bo = to_vc4_bo(&drm_fb_cma_get_gem_obj(state->fb, 0)->base);

	drm_gem_fb_prepare_fb(plane, state);

	if (plane->state->fb == state->fb)
		return 0;

	ret = vc4_bo_inc_usecnt(bo);
	if (ret)
		return ret;

	return 0;
}