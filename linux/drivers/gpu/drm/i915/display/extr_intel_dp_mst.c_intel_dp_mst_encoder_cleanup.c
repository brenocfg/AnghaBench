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
struct intel_dp {int /*<<< orphan*/  mst_mgr; int /*<<< orphan*/  can_mst; } ;
struct intel_digital_port {struct intel_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_destroy (int /*<<< orphan*/ *) ; 

void
intel_dp_mst_encoder_cleanup(struct intel_digital_port *intel_dig_port)
{
	struct intel_dp *intel_dp = &intel_dig_port->dp;

	if (!intel_dp->can_mst)
		return;

	drm_dp_mst_topology_mgr_destroy(&intel_dp->mst_mgr);
	/* encoders will get killed by normal cleanup */
}