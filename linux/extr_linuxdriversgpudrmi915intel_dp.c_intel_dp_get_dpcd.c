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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dp {int* dpcd; int /*<<< orphan*/  downstream_ports; int /*<<< orphan*/  aux; int /*<<< orphan*/  sink_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DOWNSTREAM_PORT_0 ; 
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_GET_SINK_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_MAX_DOWNSTREAM_PORTS ; 
 int /*<<< orphan*/  DP_SINK_COUNT ; 
 scalar_t__ drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_is_branch (int*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_read_dpcd (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_common_rates (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_sink_rates (struct intel_dp*) ; 

__attribute__((used)) static bool
intel_dp_get_dpcd(struct intel_dp *intel_dp)
{
	u8 sink_count;

	if (!intel_dp_read_dpcd(intel_dp))
		return false;

	/* Don't clobber cached eDP rates. */
	if (!intel_dp_is_edp(intel_dp)) {
		intel_dp_set_sink_rates(intel_dp);
		intel_dp_set_common_rates(intel_dp);
	}

	if (drm_dp_dpcd_readb(&intel_dp->aux, DP_SINK_COUNT, &sink_count) <= 0)
		return false;

	/*
	 * Sink count can change between short pulse hpd hence
	 * a member variable in intel_dp will track any changes
	 * between short pulse interrupts.
	 */
	intel_dp->sink_count = DP_GET_SINK_COUNT(sink_count);

	/*
	 * SINK_COUNT == 0 and DOWNSTREAM_PORT_PRESENT == 1 implies that
	 * a dongle is present but no display. Unless we require to know
	 * if a dongle is present or not, we don't need to update
	 * downstream port information. So, an early return here saves
	 * time from performing other operations which are not required.
	 */
	if (!intel_dp_is_edp(intel_dp) && !intel_dp->sink_count)
		return false;

	if (!drm_dp_is_branch(intel_dp->dpcd))
		return true; /* native DP sink */

	if (intel_dp->dpcd[DP_DPCD_REV] == 0x10)
		return true; /* no per-port downstream info */

	if (drm_dp_dpcd_read(&intel_dp->aux, DP_DOWNSTREAM_PORT_0,
			     intel_dp->downstream_ports,
			     DP_MAX_DOWNSTREAM_PORTS) < 0)
		return false; /* downstream port status fetch failed */

	return true;
}