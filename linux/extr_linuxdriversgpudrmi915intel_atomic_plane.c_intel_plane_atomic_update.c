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
struct TYPE_2__ {scalar_t__ visible; int /*<<< orphan*/  crtc; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_plane {int /*<<< orphan*/  (* disable_plane ) (struct intel_plane*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update_plane ) (struct intel_plane*,struct intel_crtc_state const*,struct intel_plane_state const*) ;} ;
struct intel_crtc_state {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_plane_state {struct drm_crtc* crtc; int /*<<< orphan*/  state; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,int /*<<< orphan*/ ) ; 
 struct intel_plane_state* intel_atomic_get_new_plane_state (struct intel_atomic_state*,struct intel_plane*) ; 
 int /*<<< orphan*/  stub1 (struct intel_plane*,struct intel_crtc_state const*,struct intel_plane_state const*) ; 
 int /*<<< orphan*/  stub2 (struct intel_plane*,int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_crtc (struct drm_crtc*) ; 
 struct intel_plane* to_intel_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  trace_intel_disable_plane (struct drm_plane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_update_plane (struct drm_plane*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_plane_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct intel_atomic_state *state = to_intel_atomic_state(old_state->state);
	struct intel_plane *intel_plane = to_intel_plane(plane);
	const struct intel_plane_state *new_plane_state =
		intel_atomic_get_new_plane_state(state, intel_plane);
	struct drm_crtc *crtc = new_plane_state->base.crtc ?: old_state->crtc;

	if (new_plane_state->base.visible) {
		const struct intel_crtc_state *new_crtc_state =
			intel_atomic_get_new_crtc_state(state, to_intel_crtc(crtc));

		trace_intel_update_plane(plane,
					 to_intel_crtc(crtc));

		intel_plane->update_plane(intel_plane,
					  new_crtc_state, new_plane_state);
	} else {
		trace_intel_disable_plane(plane,
					  to_intel_crtc(crtc));

		intel_plane->disable_plane(intel_plane, to_intel_crtc(crtc));
	}
}