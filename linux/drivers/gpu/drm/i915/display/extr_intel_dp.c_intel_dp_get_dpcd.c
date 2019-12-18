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
struct intel_dp {int* dpcd; int /*<<< orphan*/  downstream_ports; int /*<<< orphan*/  aux; int /*<<< orphan*/  sink_count; int /*<<< orphan*/  desc; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DOWNSTREAM_PORT_0 ; 
 int /*<<< orphan*/  DP_DPCD_QUIRK_NO_SINK_COUNT ; 
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_GET_SINK_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_MAX_DOWNSTREAM_PORTS ; 
 int /*<<< orphan*/  DP_SINK_COUNT ; 
 scalar_t__ drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_has_quirk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_is_branch (int*) ; 
 int /*<<< orphan*/  drm_dp_read_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_read_dpcd (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_common_rates (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_sink_rates (struct intel_dp*) ; 

__attribute__((used)) static bool
intel_dp_get_dpcd(struct intel_dp *intel_dp)
{
	if (!intel_dp_read_dpcd(intel_dp))
		return false;

	/*
	 * Don't clobber cached eDP rates. Also skip re-reading
	 * the OUI/ID since we know it won't change.
	 */
	if (!intel_dp_is_edp(intel_dp)) {
		drm_dp_read_desc(&intel_dp->aux, &intel_dp->desc,
				 drm_dp_is_branch(intel_dp->dpcd));

		intel_dp_set_sink_rates(intel_dp);
		intel_dp_set_common_rates(intel_dp);
	}

	/*
	 * Some eDP panels do not set a valid value for sink count, that is why
	 * it don't care about read it here and in intel_edp_init_dpcd().
	 */
	if (!intel_dp_is_edp(intel_dp) &&
	    !drm_dp_has_quirk(&intel_dp->desc, DP_DPCD_QUIRK_NO_SINK_COUNT)) {
		u8 count;
		ssize_t r;

		r = drm_dp_dpcd_readb(&intel_dp->aux, DP_SINK_COUNT, &count);
		if (r < 1)
			return false;

		/*
		 * Sink count can change between short pulse hpd hence
		 * a member variable in intel_dp will track any changes
		 * between short pulse interrupts.
		 */
		intel_dp->sink_count = DP_GET_SINK_COUNT(count);

		/*
		 * SINK_COUNT == 0 and DOWNSTREAM_PORT_PRESENT == 1 implies that
		 * a dongle is present but no display. Unless we require to know
		 * if a dongle is present or not, we don't need to update
		 * downstream port information. So, an early return here saves
		 * time from performing other operations which are not required.
		 */
		if (!intel_dp->sink_count)
			return false;
	}

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