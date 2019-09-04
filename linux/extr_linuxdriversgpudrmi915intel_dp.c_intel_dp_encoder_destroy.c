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
struct TYPE_2__ {int /*<<< orphan*/ * notifier_call; } ;
struct intel_dp {TYPE_1__ edp_notifier; int /*<<< orphan*/  panel_vdd_work; } ;
struct intel_digital_port {struct intel_dp dp; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  edp_panel_vdd_off_sync (struct intel_dp*) ; 
 struct intel_digital_port* enc_to_dig_port (struct drm_encoder*) ; 
 int /*<<< orphan*/  intel_dp_aux_fini (struct intel_dp*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_mst_encoder_cleanup (struct intel_digital_port*) ; 
 int /*<<< orphan*/  kfree (struct intel_digital_port*) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (TYPE_1__*) ; 

void intel_dp_encoder_destroy(struct drm_encoder *encoder)
{
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(encoder);
	struct intel_dp *intel_dp = &intel_dig_port->dp;

	intel_dp_mst_encoder_cleanup(intel_dig_port);
	if (intel_dp_is_edp(intel_dp)) {
		cancel_delayed_work_sync(&intel_dp->panel_vdd_work);
		/*
		 * vdd might still be enabled do to the delayed vdd off.
		 * Make sure vdd is actually turned off here.
		 */
		pps_lock(intel_dp);
		edp_panel_vdd_off_sync(intel_dp);
		pps_unlock(intel_dp);

		if (intel_dp->edp_notifier.notifier_call) {
			unregister_reboot_notifier(&intel_dp->edp_notifier);
			intel_dp->edp_notifier.notifier_call = NULL;
		}
	}

	intel_dp_aux_fini(intel_dp);

	drm_encoder_cleanup(encoder);
	kfree(intel_dig_port);
}