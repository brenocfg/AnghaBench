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
struct intel_plane_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct intel_plane {scalar_t__ id; int /*<<< orphan*/  (* disable_plane ) (struct intel_plane*,struct intel_crtc*) ;TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct intel_crtc {TYPE_2__ base; } ;

/* Variables and functions */
 scalar_t__ PLANE_PRIMARY ; 
 int /*<<< orphan*/  fixup_active_planes (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_pre_disable_primary_noatomic (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_set_plane_visible (struct intel_crtc_state*,struct intel_plane_state*,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_plane*,struct intel_crtc*) ; 
 struct intel_crtc_state* to_intel_crtc_state (int /*<<< orphan*/ ) ; 
 struct intel_plane_state* to_intel_plane_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_disable_plane (TYPE_1__*,struct intel_crtc*) ; 

__attribute__((used)) static void intel_plane_disable_noatomic(struct intel_crtc *crtc,
					 struct intel_plane *plane)
{
	struct intel_crtc_state *crtc_state =
		to_intel_crtc_state(crtc->base.state);
	struct intel_plane_state *plane_state =
		to_intel_plane_state(plane->base.state);

	intel_set_plane_visible(crtc_state, plane_state, false);
	fixup_active_planes(crtc_state);

	if (plane->id == PLANE_PRIMARY)
		intel_pre_disable_primary_noatomic(&crtc->base);

	trace_intel_disable_plane(&plane->base, crtc);
	plane->disable_plane(plane, crtc);
}