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
typedef  size_t u32 ;
struct sseu_dev_info {int /*<<< orphan*/ * subslice_mask; int /*<<< orphan*/  slice_mask; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct sseu_dev_info sseu; } ;

/* Variables and functions */
 size_t GEN11_MCR_SLICE (size_t) ; 
 size_t GEN11_MCR_SUBSLICE (size_t) ; 
 size_t GEN8_MCR_SLICE (size_t) ; 
 size_t GEN8_MCR_SUBSLICE (size_t) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 size_t fls (int /*<<< orphan*/ ) ; 

u32 intel_calculate_mcr_s_ss_select(struct drm_i915_private *dev_priv)
{
	const struct sseu_dev_info *sseu = &(INTEL_INFO(dev_priv)->sseu);
	u32 mcr_s_ss_select;
	u32 slice = fls(sseu->slice_mask);
	u32 subslice = fls(sseu->subslice_mask[slice]);

	if (INTEL_GEN(dev_priv) == 10)
		mcr_s_ss_select = GEN8_MCR_SLICE(slice) |
				  GEN8_MCR_SUBSLICE(subslice);
	else if (INTEL_GEN(dev_priv) >= 11)
		mcr_s_ss_select = GEN11_MCR_SLICE(slice) |
				  GEN11_MCR_SUBSLICE(subslice);
	else
		mcr_s_ss_select = 0;

	return mcr_s_ss_select;
}