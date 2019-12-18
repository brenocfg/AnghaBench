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
typedef  int u8 ;
typedef  int u32 ;
struct sseu_dev_info {int slice_mask; int max_slices; int max_subslices; int max_eus_per_subslice; int* subslice_mask; int* subslice_7eu; int has_slice_pg; scalar_t__ has_eu_pg; scalar_t__ has_subslice_pg; int /*<<< orphan*/  eu_total; int /*<<< orphan*/  eu_per_subslice; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct sseu_dev_info sseu; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,scalar_t__) ; 
 int GEN8_EU_DIS0_S0_MASK ; 
 int GEN8_EU_DIS0_S1_SHIFT ; 
 int GEN8_EU_DIS1_S1_MASK ; 
 int GEN8_EU_DIS1_S2_SHIFT ; 
 int GEN8_EU_DIS2_S2_MASK ; 
 int /*<<< orphan*/  GEN8_EU_DISABLE0 ; 
 int /*<<< orphan*/  GEN8_EU_DISABLE1 ; 
 int /*<<< orphan*/  GEN8_EU_DISABLE2 ; 
 int GEN8_F2_SS_DIS_MASK ; 
 int GEN8_F2_SS_DIS_SHIFT ; 
 int GEN8_F2_S_ENA_MASK ; 
 int GEN8_F2_S_ENA_SHIFT ; 
 int /*<<< orphan*/  GEN8_FUSE2 ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  compute_eu_total (struct sseu_dev_info*) ; 
 int hweight8 (int) ; 
 scalar_t__ intel_sseu_subslice_total (struct sseu_dev_info*) ; 
 int /*<<< orphan*/  sseu_set_eus (struct sseu_dev_info*,int,int,int) ; 

__attribute__((used)) static void broadwell_sseu_info_init(struct drm_i915_private *dev_priv)
{
	struct sseu_dev_info *sseu = &RUNTIME_INFO(dev_priv)->sseu;
	int s, ss;
	u32 fuse2, subslice_mask, eu_disable[3]; /* s_max */

	fuse2 = I915_READ(GEN8_FUSE2);
	sseu->slice_mask = (fuse2 & GEN8_F2_S_ENA_MASK) >> GEN8_F2_S_ENA_SHIFT;
	sseu->max_slices = 3;
	sseu->max_subslices = 3;
	sseu->max_eus_per_subslice = 8;

	/*
	 * The subslice disable field is global, i.e. it applies
	 * to each of the enabled slices.
	 */
	subslice_mask = GENMASK(sseu->max_subslices - 1, 0);
	subslice_mask &= ~((fuse2 & GEN8_F2_SS_DIS_MASK) >>
			   GEN8_F2_SS_DIS_SHIFT);

	eu_disable[0] = I915_READ(GEN8_EU_DISABLE0) & GEN8_EU_DIS0_S0_MASK;
	eu_disable[1] = (I915_READ(GEN8_EU_DISABLE0) >> GEN8_EU_DIS0_S1_SHIFT) |
			((I915_READ(GEN8_EU_DISABLE1) & GEN8_EU_DIS1_S1_MASK) <<
			 (32 - GEN8_EU_DIS0_S1_SHIFT));
	eu_disable[2] = (I915_READ(GEN8_EU_DISABLE1) >> GEN8_EU_DIS1_S2_SHIFT) |
			((I915_READ(GEN8_EU_DISABLE2) & GEN8_EU_DIS2_S2_MASK) <<
			 (32 - GEN8_EU_DIS1_S2_SHIFT));

	/*
	 * Iterate through enabled slices and subslices to
	 * count the total enabled EU.
	 */
	for (s = 0; s < sseu->max_slices; s++) {
		if (!(sseu->slice_mask & BIT(s)))
			/* skip disabled slice */
			continue;

		sseu->subslice_mask[s] = subslice_mask;

		for (ss = 0; ss < sseu->max_subslices; ss++) {
			u8 eu_disabled_mask;
			u32 n_disabled;

			if (!(sseu->subslice_mask[s] & BIT(ss)))
				/* skip disabled subslice */
				continue;

			eu_disabled_mask =
				eu_disable[s] >> (ss * sseu->max_eus_per_subslice);

			sseu_set_eus(sseu, s, ss, ~eu_disabled_mask);

			n_disabled = hweight8(eu_disabled_mask);

			/*
			 * Record which subslices have 7 EUs.
			 */
			if (sseu->max_eus_per_subslice - n_disabled == 7)
				sseu->subslice_7eu[s] |= 1 << ss;
		}
	}

	sseu->eu_total = compute_eu_total(sseu);

	/*
	 * BDW is expected to always have a uniform distribution of EU across
	 * subslices with the exception that any one EU in any one subslice may
	 * be fused off for die recovery.
	 */
	sseu->eu_per_subslice = intel_sseu_subslice_total(sseu) ?
				DIV_ROUND_UP(sseu->eu_total,
					     intel_sseu_subslice_total(sseu)) :
				0;

	/*
	 * BDW supports slice power gating on devices with more than
	 * one slice.
	 */
	sseu->has_slice_pg = hweight8(sseu->slice_mask) > 1;
	sseu->has_subslice_pg = 0;
	sseu->has_eu_pg = 0;
}