#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {scalar_t__ fb; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct atmel_hlcdc_plane_state {TYPE_2__** dscrs; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/  dscrpool; } ;
struct TYPE_5__ {int /*<<< orphan*/  self; } ;
struct TYPE_4__ {struct atmel_hlcdc_dc* dev_private; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__**) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_put (scalar_t__) ; 
 struct atmel_hlcdc_plane_state* drm_plane_state_to_atmel_hlcdc_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  kfree (struct atmel_hlcdc_plane_state*) ; 

__attribute__((used)) static void atmel_hlcdc_plane_atomic_destroy_state(struct drm_plane *p,
						   struct drm_plane_state *s)
{
	struct atmel_hlcdc_plane_state *state =
			drm_plane_state_to_atmel_hlcdc_plane_state(s);
	struct atmel_hlcdc_dc *dc = p->dev->dev_private;
	int i;

	for (i = 0; i < ARRAY_SIZE(state->dscrs); i++) {
		dma_pool_free(dc->dscrpool, state->dscrs[i],
			      state->dscrs[i]->self);
	}

	if (s->fb)
		drm_framebuffer_put(s->fb);

	kfree(state);
}