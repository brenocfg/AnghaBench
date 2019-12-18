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
 struct vc4_bo* to_vc4_bo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_bo_dec_usecnt (struct vc4_bo*) ; 

__attribute__((used)) static void vc4_cleanup_fb(struct drm_plane *plane,
			   struct drm_plane_state *state)
{
	struct vc4_bo *bo;

	if (plane->state->fb == state->fb || !state->fb)
		return;

	bo = to_vc4_bo(&drm_fb_cma_get_gem_obj(state->fb, 0)->base);
	vc4_bo_dec_usecnt(bo);
}