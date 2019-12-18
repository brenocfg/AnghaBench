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
struct TYPE_2__ {struct drm_plane* plane; scalar_t__ fb; } ;
struct mdp5_plane_state {int alpha; TYPE_1__ base; scalar_t__ zpos; scalar_t__ premultiplied; } ;
struct drm_plane {scalar_t__ type; TYPE_1__* state; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ STAGE0 ; 
 scalar_t__ STAGE_BASE ; 
 int /*<<< orphan*/  drm_framebuffer_put (scalar_t__) ; 
 scalar_t__ drm_plane_index (struct drm_plane*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct mdp5_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp5_plane_state (TYPE_1__*) ; 

__attribute__((used)) static void mdp5_plane_reset(struct drm_plane *plane)
{
	struct mdp5_plane_state *mdp5_state;

	if (plane->state && plane->state->fb)
		drm_framebuffer_put(plane->state->fb);

	kfree(to_mdp5_plane_state(plane->state));
	mdp5_state = kzalloc(sizeof(*mdp5_state), GFP_KERNEL);

	/* assign default blend parameters */
	mdp5_state->alpha = 255;
	mdp5_state->premultiplied = 0;

	if (plane->type == DRM_PLANE_TYPE_PRIMARY)
		mdp5_state->zpos = STAGE_BASE;
	else
		mdp5_state->zpos = STAGE0 + drm_plane_index(plane);

	mdp5_state->base.plane = plane;

	plane->state = &mdp5_state->base;
}