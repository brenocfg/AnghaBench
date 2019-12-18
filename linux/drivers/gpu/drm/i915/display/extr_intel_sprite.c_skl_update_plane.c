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
struct intel_plane_state {int /*<<< orphan*/  ctl; scalar_t__ linked_plane; } ;
struct intel_plane {int dummy; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_program_plane (struct intel_plane*,struct intel_crtc_state const*,struct intel_plane_state const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_update_plane(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	int color_plane = 0;

	if (plane_state->linked_plane) {
		/* Program the UV plane */
		color_plane = 1;
	}

	skl_program_plane(plane, crtc_state, plane_state,
			  color_plane, false, plane_state->ctl);
}