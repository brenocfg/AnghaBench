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
struct intel_plane_state {int ctl; } ;
struct intel_plane {int dummy; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int PLANE_CTL_YUV420_Y_PLANE ; 
 int /*<<< orphan*/  skl_program_plane (struct intel_plane*,struct intel_crtc_state const*,struct intel_plane_state const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
icl_update_slave(struct intel_plane *plane,
		 const struct intel_crtc_state *crtc_state,
		 const struct intel_plane_state *plane_state)
{
	skl_program_plane(plane, crtc_state, plane_state, 0, true,
			  plane_state->ctl | PLANE_CTL_YUV420_Y_PLANE);
}