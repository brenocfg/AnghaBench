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
struct intel_plane {int /*<<< orphan*/  (* disable_plane ) (struct intel_plane*,struct intel_crtc_state const*) ;int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intel_plane*,struct intel_crtc_state const*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_disable_plane (int /*<<< orphan*/ *,struct intel_crtc*) ; 

void intel_disable_plane(struct intel_plane *plane,
			 const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);

	trace_intel_disable_plane(&plane->base, crtc);
	plane->disable_plane(plane, crtc_state);
}