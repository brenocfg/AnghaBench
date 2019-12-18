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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sseu_dev_info {int slice_mask; int eu_per_subslice; int eu_total; int /*<<< orphan*/ * subslice_mask; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int eu_per_subslice; int /*<<< orphan*/ * subslice_7eu; int /*<<< orphan*/ * subslice_mask; } ;
struct TYPE_4__ {TYPE_1__ sseu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_GT_SLICE_INFO ; 
 int GEN8_LSLICESTAT_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_2__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int fls (int) ; 
 scalar_t__ hweight8 (int /*<<< orphan*/ ) ; 
 int intel_sseu_subslice_total (struct sseu_dev_info*) ; 

__attribute__((used)) static void broadwell_sseu_device_status(struct drm_i915_private *dev_priv,
					 struct sseu_dev_info *sseu)
{
	u32 slice_info = I915_READ(GEN8_GT_SLICE_INFO);
	int s;

	sseu->slice_mask = slice_info & GEN8_LSLICESTAT_MASK;

	if (sseu->slice_mask) {
		sseu->eu_per_subslice =
			RUNTIME_INFO(dev_priv)->sseu.eu_per_subslice;
		for (s = 0; s < fls(sseu->slice_mask); s++) {
			sseu->subslice_mask[s] =
				RUNTIME_INFO(dev_priv)->sseu.subslice_mask[s];
		}
		sseu->eu_total = sseu->eu_per_subslice *
				 intel_sseu_subslice_total(sseu);

		/* subtract fused off EU(s) from enabled slice(s) */
		for (s = 0; s < fls(sseu->slice_mask); s++) {
			u8 subslice_7eu =
				RUNTIME_INFO(dev_priv)->sseu.subslice_7eu[s];

			sseu->eu_total -= hweight8(subslice_7eu);
		}
	}
}