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
struct nv50_atom {int /*<<< orphan*/  state; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_state_default_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nv50_atom*) ; 
 struct nv50_atom* nv50_atom (struct drm_atomic_state*) ; 

__attribute__((used)) static void
nv50_disp_atomic_state_free(struct drm_atomic_state *state)
{
	struct nv50_atom *atom = nv50_atom(state);
	drm_atomic_state_default_release(&atom->state);
	kfree(atom);
}