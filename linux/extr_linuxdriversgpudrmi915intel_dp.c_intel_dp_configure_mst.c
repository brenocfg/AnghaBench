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
struct intel_dp {scalar_t__ is_mst; int /*<<< orphan*/  mst_mgr; int /*<<< orphan*/  can_mst; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_dp_mst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ i915_modparams ; 
 scalar_t__ intel_dp_can_mst (struct intel_dp*) ; 

__attribute__((used)) static void
intel_dp_configure_mst(struct intel_dp *intel_dp)
{
	if (!i915_modparams.enable_dp_mst)
		return;

	if (!intel_dp->can_mst)
		return;

	intel_dp->is_mst = intel_dp_can_mst(intel_dp);

	if (intel_dp->is_mst)
		DRM_DEBUG_KMS("Sink is MST capable\n");
	else
		DRM_DEBUG_KMS("Sink is not MST capable\n");

	drm_dp_mst_topology_mgr_set_mst(&intel_dp->mst_mgr,
					intel_dp->is_mst);
}