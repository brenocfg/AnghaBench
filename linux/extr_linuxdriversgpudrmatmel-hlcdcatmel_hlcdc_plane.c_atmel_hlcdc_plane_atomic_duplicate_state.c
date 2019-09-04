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
struct drm_plane_state {scalar_t__ fb; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;
struct atmel_hlcdc_plane_state {struct drm_plane_state base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ atmel_hlcdc_plane_alloc_dscrs (struct drm_plane*,struct atmel_hlcdc_plane_state*) ; 
 int /*<<< orphan*/  drm_framebuffer_get (scalar_t__) ; 
 struct atmel_hlcdc_plane_state* drm_plane_state_to_atmel_hlcdc_plane_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atmel_hlcdc_plane_state*) ; 
 struct atmel_hlcdc_plane_state* kmemdup (struct atmel_hlcdc_plane_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_plane_state *
atmel_hlcdc_plane_atomic_duplicate_state(struct drm_plane *p)
{
	struct atmel_hlcdc_plane_state *state =
			drm_plane_state_to_atmel_hlcdc_plane_state(p->state);
	struct atmel_hlcdc_plane_state *copy;

	copy = kmemdup(state, sizeof(*state), GFP_KERNEL);
	if (!copy)
		return NULL;

	if (atmel_hlcdc_plane_alloc_dscrs(p, copy)) {
		kfree(copy);
		return NULL;
	}

	if (copy->base.fb)
		drm_framebuffer_get(copy->base.fb);

	return &copy->base;
}