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
struct TYPE_4__ {char* mst_state; } ;
struct intel_dp {int reset_link_params; int is_mst; TYPE_2__ mst_mgr; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  port; } ;
struct intel_digital_port {TYPE_1__ base; struct intel_dp dp; } ;
typedef  enum irqreturn { ____Placeholder_irqreturn } irqreturn ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INTEL_OUTPUT_EDP ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (TYPE_2__*,int) ; 
 int /*<<< orphan*/  intel_dp_check_mst_status (struct intel_dp*) ; 
 int intel_dp_short_pulse (struct intel_dp*) ; 
 int port_name (int /*<<< orphan*/ ) ; 

enum irqreturn
intel_dp_hpd_pulse(struct intel_digital_port *intel_dig_port, bool long_hpd)
{
	struct intel_dp *intel_dp = &intel_dig_port->dp;

	if (long_hpd && intel_dig_port->base.type == INTEL_OUTPUT_EDP) {
		/*
		 * vdd off can generate a long pulse on eDP which
		 * would require vdd on to handle it, and thus we
		 * would end up in an endless cycle of
		 * "vdd off -> long hpd -> vdd on -> detect -> vdd off -> ..."
		 */
		DRM_DEBUG_KMS("ignoring long hpd on eDP port %c\n",
			      port_name(intel_dig_port->base.port));
		return IRQ_HANDLED;
	}

	DRM_DEBUG_KMS("got hpd irq on port %c - %s\n",
		      port_name(intel_dig_port->base.port),
		      long_hpd ? "long" : "short");

	if (long_hpd) {
		intel_dp->reset_link_params = true;
		return IRQ_NONE;
	}

	if (intel_dp->is_mst) {
		if (intel_dp_check_mst_status(intel_dp) == -EINVAL) {
			/*
			 * If we were in MST mode, and device is not
			 * there, get out of MST mode
			 */
			DRM_DEBUG_KMS("MST device may have disappeared %d vs %d\n",
				      intel_dp->is_mst, intel_dp->mst_mgr.mst_state);
			intel_dp->is_mst = false;
			drm_dp_mst_topology_mgr_set_mst(&intel_dp->mst_mgr,
							intel_dp->is_mst);

			return IRQ_NONE;
		}
	}

	if (!intel_dp->is_mst) {
		bool handled;

		handled = intel_dp_short_pulse(intel_dp);

		if (!handled)
			return IRQ_NONE;
	}

	return IRQ_HANDLED;
}