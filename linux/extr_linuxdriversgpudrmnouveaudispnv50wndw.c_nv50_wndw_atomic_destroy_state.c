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
struct nv50_wndw_atom {int /*<<< orphan*/  state; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nv50_wndw_atom*) ; 
 struct nv50_wndw_atom* nv50_wndw_atom (struct drm_plane_state*) ; 

__attribute__((used)) static void
nv50_wndw_atomic_destroy_state(struct drm_plane *plane,
			       struct drm_plane_state *state)
{
	struct nv50_wndw_atom *asyw = nv50_wndw_atom(state);
	__drm_atomic_helper_plane_destroy_state(&asyw->state);
	kfree(asyw);
}