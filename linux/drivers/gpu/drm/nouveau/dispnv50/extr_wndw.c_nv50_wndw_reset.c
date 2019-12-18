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
struct nv50_wndw_atom {int /*<<< orphan*/  state; } ;
struct drm_plane {TYPE_2__* state; TYPE_1__* funcs; } ;
struct TYPE_4__ {void* normalized_zpos; void* zpos; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* atomic_destroy_state ) (struct drm_plane*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 struct nv50_wndw_atom* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* nv50_wndw_zpos_default (struct drm_plane*) ; 
 int /*<<< orphan*/  stub1 (struct drm_plane*,TYPE_2__*) ; 

__attribute__((used)) static void
nv50_wndw_reset(struct drm_plane *plane)
{
	struct nv50_wndw_atom *asyw;

	if (WARN_ON(!(asyw = kzalloc(sizeof(*asyw), GFP_KERNEL))))
		return;

	if (plane->state)
		plane->funcs->atomic_destroy_state(plane, plane->state);

	__drm_atomic_helper_plane_reset(plane, &asyw->state);
	plane->state->zpos = nv50_wndw_zpos_default(plane);
	plane->state->normalized_zpos = nv50_wndw_zpos_default(plane);
}