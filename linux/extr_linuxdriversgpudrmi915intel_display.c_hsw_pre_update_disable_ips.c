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
struct intel_crtc_state {int /*<<< orphan*/  ips_enabled; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ needs_modeset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hsw_pre_update_disable_ips(const struct intel_crtc_state *old_crtc_state,
				       const struct intel_crtc_state *new_crtc_state)
{
	if (!old_crtc_state->ips_enabled)
		return false;

	if (needs_modeset(&new_crtc_state->base))
		return true;

	return !new_crtc_state->ips_enabled;
}