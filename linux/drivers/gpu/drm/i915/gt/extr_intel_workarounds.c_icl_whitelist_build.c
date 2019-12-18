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
struct i915_wa_list {int dummy; } ;
struct intel_engine_cs {int class; int /*<<< orphan*/  mmio_base; struct i915_wa_list whitelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN10_SAMPLER_MODE ; 
 int /*<<< orphan*/  GEN9_HALF_SLICE_CHICKEN7 ; 
 int /*<<< orphan*/  GEN9_SLICE_COMMON_ECO_CHICKEN1 ; 
 int /*<<< orphan*/  PS_INVOCATION_COUNT ; 
#define  RENDER_CLASS 129 
 int RING_FORCE_TO_NONPRIV_ACCESS_RD ; 
 int RING_FORCE_TO_NONPRIV_RANGE_4 ; 
#define  VIDEO_DECODE_CLASS 128 
 int /*<<< orphan*/  _MMIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whitelist_reg (struct i915_wa_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whitelist_reg_ext (struct i915_wa_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icl_whitelist_build(struct intel_engine_cs *engine)
{
	struct i915_wa_list *w = &engine->whitelist;

	switch (engine->class) {
	case RENDER_CLASS:
		/* WaAllowUMDToModifyHalfSliceChicken7:icl */
		whitelist_reg(w, GEN9_HALF_SLICE_CHICKEN7);

		/* WaAllowUMDToModifySamplerMode:icl */
		whitelist_reg(w, GEN10_SAMPLER_MODE);

		/* WaEnableStateCacheRedirectToCS:icl */
		whitelist_reg(w, GEN9_SLICE_COMMON_ECO_CHICKEN1);

		/*
		 * WaAllowPMDepthAndInvocationCountAccessFromUMD:icl
		 *
		 * This covers 4 register which are next to one another :
		 *   - PS_INVOCATION_COUNT
		 *   - PS_INVOCATION_COUNT_UDW
		 *   - PS_DEPTH_COUNT
		 *   - PS_DEPTH_COUNT_UDW
		 */
		whitelist_reg_ext(w, PS_INVOCATION_COUNT,
				  RING_FORCE_TO_NONPRIV_ACCESS_RD |
				  RING_FORCE_TO_NONPRIV_RANGE_4);
		break;

	case VIDEO_DECODE_CLASS:
		/* hucStatusRegOffset */
		whitelist_reg_ext(w, _MMIO(0x2000 + engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		/* hucUKernelHdrInfoRegOffset */
		whitelist_reg_ext(w, _MMIO(0x2014 + engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		/* hucStatus2RegOffset */
		whitelist_reg_ext(w, _MMIO(0x23B0 + engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		break;

	default:
		break;
	}
}