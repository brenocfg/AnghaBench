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
struct TYPE_3__ {int private_flags; } ;
struct TYPE_4__ {TYPE_1__ adjusted_mode; } ;
struct intel_crtc_state {int /*<<< orphan*/  ips_enabled; TYPE_2__ base; scalar_t__ update_pipe; } ;

/* Variables and functions */
 int I915_MODE_FLAG_INHERITED ; 
 scalar_t__ needs_modeset (TYPE_2__*) ; 

__attribute__((used)) static bool hsw_post_update_enable_ips(const struct intel_crtc_state *old_crtc_state,
				       const struct intel_crtc_state *new_crtc_state)
{
	if (!new_crtc_state->ips_enabled)
		return false;

	if (needs_modeset(&new_crtc_state->base))
		return true;

	/*
	 * We can't read out IPS on broadwell, assume the worst and
	 * forcibly enable IPS on the first fastset.
	 */
	if (new_crtc_state->update_pipe &&
	    old_crtc_state->base.adjusted_mode.private_flags & I915_MODE_FLAG_INHERITED)
		return true;

	return !old_crtc_state->ips_enabled;
}