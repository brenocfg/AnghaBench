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
struct sseu_dev_info {int slice_mask; int max_slices; int max_subslices; int max_eus_per_subslice; int* subslice_mask; int* subslice_7eu; int eu_per_subslice; int has_slice_pg; int has_subslice_pg; int has_eu_pg; int min_eu_in_pool; int /*<<< orphan*/  eu_total; } ;
struct intel_device_info {int has_pooled_eu; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct sseu_dev_info sseu; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int GEN8_F2_S_ENA_MASK ; 
 int GEN8_F2_S_ENA_SHIFT ; 
 int /*<<< orphan*/  GEN8_FUSE2 ; 
 int /*<<< orphan*/  GEN9_EU_DISABLE (int) ; 
 int GEN9_F2_SS_DIS_MASK ; 
 int GEN9_F2_SS_DIS_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_SS_DISABLED (int) ; 
 TYPE_1__* RUNTIME_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  compute_eu_total (struct sseu_dev_info*) ; 
 int hweight8 (int) ; 
 int intel_sseu_subslice_total (struct sseu_dev_info*) ; 
 struct intel_device_info* mkwrite_device_info (struct drm_i915_private*) ; 
 int /*<<< orphan*/  sseu_set_eus (struct sseu_dev_info*,int,int,int) ; 

__attribute__((used)) static void gen9_sseu_info_init(struct drm_i915_private *dev_priv)
{
	struct intel_device_info *info = mkwrite_device_info(dev_priv);
	struct sseu_dev_info *sseu = &RUNTIME_INFO(dev_priv)->sseu;
	int s, ss;
	u32 fuse2, eu_disable, subslice_mask;
	const u8 eu_mask = 0xff;

	fuse2 = I915_READ(GEN8_FUSE2);
	sseu->slice_mask = (fuse2 & GEN8_F2_S_ENA_MASK) >> GEN8_F2_S_ENA_SHIFT;

	/* BXT has a single slice and at most 3 subslices. */
	sseu->max_slices = IS_GEN9_LP(dev_priv) ? 1 : 3;
	sseu->max_subslices = IS_GEN9_LP(dev_priv) ? 3 : 4;
	sseu->max_eus_per_subslice = 8;

	/*
	 * The subslice disable field is global, i.e. it applies
	 * to each of the enabled slices.
	*/
	subslice_mask = (1 << sseu->max_subslices) - 1;
	subslice_mask &= ~((fuse2 & GEN9_F2_SS_DIS_MASK) >>
			   GEN9_F2_SS_DIS_SHIFT);

	/*
	 * Iterate through enabled slices and subslices to
	 * count the total enabled EU.
	*/
	for (s = 0; s < sseu->max_slices; s++) {
		if (!(sseu->slice_mask & BIT(s)))
			/* skip disabled slice */
			continue;

		sseu->subslice_mask[s] = subslice_mask;

		eu_disable = I915_READ(GEN9_EU_DISABLE(s));
		for (ss = 0; ss < sseu->max_subslices; ss++) {
			int eu_per_ss;
			u8 eu_disabled_mask;

			if (!(sseu->subslice_mask[s] & BIT(ss)))
				/* skip disabled subslice */
				continue;

			eu_disabled_mask = (eu_disable >> (ss * 8)) & eu_mask;

			sseu_set_eus(sseu, s, ss, ~eu_disabled_mask);

			eu_per_ss = sseu->max_eus_per_subslice -
				hweight8(eu_disabled_mask);

			/*
			 * Record which subslice(s) has(have) 7 EUs. we
			 * can tune the hash used to spread work among
			 * subslices if they are unbalanced.
			 */
			if (eu_per_ss == 7)
				sseu->subslice_7eu[s] |= BIT(ss);
		}
	}

	sseu->eu_total = compute_eu_total(sseu);

	/*
	 * SKL is expected to always have a uniform distribution
	 * of EU across subslices with the exception that any one
	 * EU in any one subslice may be fused off for die
	 * recovery. BXT is expected to be perfectly uniform in EU
	 * distribution.
	*/
	sseu->eu_per_subslice = intel_sseu_subslice_total(sseu) ?
				DIV_ROUND_UP(sseu->eu_total,
					     intel_sseu_subslice_total(sseu)) :
				0;
	/*
	 * SKL+ supports slice power gating on devices with more than
	 * one slice, and supports EU power gating on devices with
	 * more than one EU pair per subslice. BXT+ supports subslice
	 * power gating on devices with more than one subslice, and
	 * supports EU power gating on devices with more than one EU
	 * pair per subslice.
	*/
	sseu->has_slice_pg =
		!IS_GEN9_LP(dev_priv) && hweight8(sseu->slice_mask) > 1;
	sseu->has_subslice_pg =
		IS_GEN9_LP(dev_priv) && intel_sseu_subslice_total(sseu) > 1;
	sseu->has_eu_pg = sseu->eu_per_subslice > 2;

	if (IS_GEN9_LP(dev_priv)) {
#define IS_SS_DISABLED(ss)	(!(sseu->subslice_mask[0] & BIT(ss)))
		info->has_pooled_eu = hweight8(sseu->subslice_mask[0]) == 3;

		sseu->min_eu_in_pool = 0;
		if (info->has_pooled_eu) {
			if (IS_SS_DISABLED(2) || IS_SS_DISABLED(0))
				sseu->min_eu_in_pool = 3;
			else if (IS_SS_DISABLED(1))
				sseu->min_eu_in_pool = 6;
			else
				sseu->min_eu_in_pool = 9;
		}
#undef IS_SS_DISABLED
	}
}