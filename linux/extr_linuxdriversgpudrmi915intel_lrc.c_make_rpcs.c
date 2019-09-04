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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int eu_per_subslice; scalar_t__ has_eu_pg; int /*<<< orphan*/ * subslice_mask; scalar_t__ has_subslice_pg; int /*<<< orphan*/  slice_mask; scalar_t__ has_slice_pg; } ;
struct TYPE_4__ {TYPE_1__ sseu; } ;

/* Variables and functions */
 int GEN8_RPCS_ENABLE ; 
 int GEN8_RPCS_EU_MAX_SHIFT ; 
 int GEN8_RPCS_EU_MIN_SHIFT ; 
 int GEN8_RPCS_SS_CNT_ENABLE ; 
 int GEN8_RPCS_SS_CNT_SHIFT ; 
 int GEN8_RPCS_S_CNT_ENABLE ; 
 int GEN8_RPCS_S_CNT_SHIFT ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 int hweight8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
make_rpcs(struct drm_i915_private *dev_priv)
{
	u32 rpcs = 0;

	/*
	 * No explicit RPCS request is needed to ensure full
	 * slice/subslice/EU enablement prior to Gen9.
	*/
	if (INTEL_GEN(dev_priv) < 9)
		return 0;

	/*
	 * Starting in Gen9, render power gating can leave
	 * slice/subslice/EU in a partially enabled state. We
	 * must make an explicit request through RPCS for full
	 * enablement.
	*/
	if (INTEL_INFO(dev_priv)->sseu.has_slice_pg) {
		rpcs |= GEN8_RPCS_S_CNT_ENABLE;
		rpcs |= hweight8(INTEL_INFO(dev_priv)->sseu.slice_mask) <<
			GEN8_RPCS_S_CNT_SHIFT;
		rpcs |= GEN8_RPCS_ENABLE;
	}

	if (INTEL_INFO(dev_priv)->sseu.has_subslice_pg) {
		rpcs |= GEN8_RPCS_SS_CNT_ENABLE;
		rpcs |= hweight8(INTEL_INFO(dev_priv)->sseu.subslice_mask[0]) <<
			GEN8_RPCS_SS_CNT_SHIFT;
		rpcs |= GEN8_RPCS_ENABLE;
	}

	if (INTEL_INFO(dev_priv)->sseu.has_eu_pg) {
		rpcs |= INTEL_INFO(dev_priv)->sseu.eu_per_subslice <<
			GEN8_RPCS_EU_MIN_SHIFT;
		rpcs |= INTEL_INFO(dev_priv)->sseu.eu_per_subslice <<
			GEN8_RPCS_EU_MAX_SHIFT;
		rpcs |= GEN8_RPCS_ENABLE;
	}

	return rpcs;
}