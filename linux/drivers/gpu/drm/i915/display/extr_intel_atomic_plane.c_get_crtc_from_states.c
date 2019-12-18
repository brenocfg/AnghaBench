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
struct TYPE_2__ {scalar_t__ crtc; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 struct intel_crtc* to_intel_crtc (scalar_t__) ; 

__attribute__((used)) static struct intel_crtc *
get_crtc_from_states(const struct intel_plane_state *old_plane_state,
		     const struct intel_plane_state *new_plane_state)
{
	if (new_plane_state->base.crtc)
		return to_intel_crtc(new_plane_state->base.crtc);

	if (old_plane_state->base.crtc)
		return to_intel_crtc(old_plane_state->base.crtc);

	return NULL;
}