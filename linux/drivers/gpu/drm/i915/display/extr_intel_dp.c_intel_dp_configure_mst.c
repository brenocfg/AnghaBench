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
struct intel_encoder {int /*<<< orphan*/  port; } ;
struct intel_dp {int can_mst; int is_mst; int /*<<< orphan*/  mst_mgr; } ;
struct TYPE_4__ {struct intel_encoder base; } ;
struct TYPE_3__ {int enable_dp_mst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ i915_modparams ; 
 int intel_dp_sink_can_mst (struct intel_dp*) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static void
intel_dp_configure_mst(struct intel_dp *intel_dp)
{
	struct intel_encoder *encoder =
		&dp_to_dig_port(intel_dp)->base;
	bool sink_can_mst = intel_dp_sink_can_mst(intel_dp);

	DRM_DEBUG_KMS("MST support? port %c: %s, sink: %s, modparam: %s\n",
		      port_name(encoder->port), yesno(intel_dp->can_mst),
		      yesno(sink_can_mst), yesno(i915_modparams.enable_dp_mst));

	if (!intel_dp->can_mst)
		return;

	intel_dp->is_mst = sink_can_mst &&
		i915_modparams.enable_dp_mst;

	drm_dp_mst_topology_mgr_set_mst(&intel_dp->mst_mgr,
					intel_dp->is_mst);
}