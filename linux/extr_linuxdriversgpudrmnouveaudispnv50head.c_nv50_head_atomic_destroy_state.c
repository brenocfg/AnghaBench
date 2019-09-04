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
struct nv50_head_atom {int /*<<< orphan*/  state; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nv50_head_atom*) ; 
 struct nv50_head_atom* nv50_head_atom (struct drm_crtc_state*) ; 

__attribute__((used)) static void
nv50_head_atomic_destroy_state(struct drm_crtc *crtc,
			       struct drm_crtc_state *state)
{
	struct nv50_head_atom *asyh = nv50_head_atom(state);
	__drm_atomic_helper_crtc_destroy_state(&asyh->state);
	kfree(asyh);
}