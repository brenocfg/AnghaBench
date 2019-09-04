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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct sseu_dev_info {size_t* subslice_mask; int /*<<< orphan*/  slice_mask; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct sseu_dev_info sseu; } ;

/* Variables and functions */
 size_t GEN10_L3BANK_MASK ; 
 size_t GEN10_L3BANK_PAIR_COUNT ; 
 int /*<<< orphan*/  GEN10_MIRROR_FUSE3 ; 
 size_t GEN11_MCR_SLICE_MASK ; 
 size_t GEN11_MCR_SUBSLICE_MASK ; 
 int /*<<< orphan*/  GEN8_MCR_SELECTOR ; 
 size_t GEN8_MCR_SLICE_MASK ; 
 size_t GEN8_MCR_SUBSLICE_MASK ; 
 size_t I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,size_t) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t fls (int /*<<< orphan*/ ) ; 
 size_t intel_calculate_mcr_s_ss_select (struct drm_i915_private*) ; 
 scalar_t__ is_power_of_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wa_init_mcr(struct drm_i915_private *dev_priv)
{
	const struct sseu_dev_info *sseu = &(INTEL_INFO(dev_priv)->sseu);
	u32 mcr;
	u32 mcr_slice_subslice_mask;

	/*
	 * WaProgramMgsrForL3BankSpecificMmioReads: cnl,icl
	 * L3Banks could be fused off in single slice scenario. If that is
	 * the case, we might need to program MCR select to a valid L3Bank
	 * by default, to make sure we correctly read certain registers
	 * later on (in the range 0xB100 - 0xB3FF).
	 * This might be incompatible with
	 * WaProgramMgsrForCorrectSliceSpecificMmioReads.
	 * Fortunately, this should not happen in production hardware, so
	 * we only assert that this is the case (instead of implementing
	 * something more complex that requires checking the range of every
	 * MMIO read).
	 */
	if (INTEL_GEN(dev_priv) >= 10 &&
	    is_power_of_2(sseu->slice_mask)) {
		/*
		 * read FUSE3 for enabled L3 Bank IDs, if L3 Bank matches
		 * enabled subslice, no need to redirect MCR packet
		 */
		u32 slice = fls(sseu->slice_mask);
		u32 fuse3 = I915_READ(GEN10_MIRROR_FUSE3);
		u8 ss_mask = sseu->subslice_mask[slice];

		u8 enabled_mask = (ss_mask | ss_mask >>
				   GEN10_L3BANK_PAIR_COUNT) & GEN10_L3BANK_MASK;
		u8 disabled_mask = fuse3 & GEN10_L3BANK_MASK;

		/*
		 * Production silicon should have matched L3Bank and
		 * subslice enabled
		 */
		WARN_ON((enabled_mask & disabled_mask) != enabled_mask);
	}

	mcr = I915_READ(GEN8_MCR_SELECTOR);

	if (INTEL_GEN(dev_priv) >= 11)
		mcr_slice_subslice_mask = GEN11_MCR_SLICE_MASK |
					  GEN11_MCR_SUBSLICE_MASK;
	else
		mcr_slice_subslice_mask = GEN8_MCR_SLICE_MASK |
					  GEN8_MCR_SUBSLICE_MASK;
	/*
	 * WaProgramMgsrForCorrectSliceSpecificMmioReads:cnl,icl
	 * Before any MMIO read into slice/subslice specific registers, MCR
	 * packet control register needs to be programmed to point to any
	 * enabled s/ss pair. Otherwise, incorrect values will be returned.
	 * This means each subsequent MMIO read will be forwarded to an
	 * specific s/ss combination, but this is OK since these registers
	 * are consistent across s/ss in almost all cases. In the rare
	 * occasions, such as INSTDONE, where this value is dependent
	 * on s/ss combo, the read should be done with read_subslice_reg.
	 */
	mcr &= ~mcr_slice_subslice_mask;
	mcr |= intel_calculate_mcr_s_ss_select(dev_priv);
	I915_WRITE(GEN8_MCR_SELECTOR, mcr);
}