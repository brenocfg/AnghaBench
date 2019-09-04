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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int /*<<< orphan*/  panel_vdd_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edp_panel_vdd_off_sync (struct intel_dp*) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 

void intel_dp_encoder_suspend(struct intel_encoder *intel_encoder)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&intel_encoder->base);

	if (!intel_dp_is_edp(intel_dp))
		return;

	/*
	 * vdd might still be enabled do to the delayed vdd off.
	 * Make sure vdd is actually turned off here.
	 */
	cancel_delayed_work_sync(&intel_dp->panel_vdd_work);
	pps_lock(intel_dp);
	edp_panel_vdd_off_sync(intel_dp);
	pps_unlock(intel_dp);
}