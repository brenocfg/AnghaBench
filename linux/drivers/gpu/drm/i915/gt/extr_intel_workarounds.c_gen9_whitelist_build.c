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

/* Variables and functions */
 int /*<<< orphan*/  COMMON_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  GEN8_CS_CHICKEN1 ; 
 int /*<<< orphan*/  GEN8_HDC_CHICKEN1 ; 
 int /*<<< orphan*/  GEN9_CTX_PREEMPT_REG ; 
 int /*<<< orphan*/  whitelist_reg (struct i915_wa_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen9_whitelist_build(struct i915_wa_list *w)
{
	/* WaVFEStateAfterPipeControlwithMediaStateClear:skl,bxt,glk,cfl */
	whitelist_reg(w, GEN9_CTX_PREEMPT_REG);

	/* WaEnablePreemptionGranularityControlByUMD:skl,bxt,kbl,cfl,[cnl] */
	whitelist_reg(w, GEN8_CS_CHICKEN1);

	/* WaAllowUMDToModifyHDCChicken1:skl,bxt,kbl,glk,cfl */
	whitelist_reg(w, GEN8_HDC_CHICKEN1);

	/* WaSendPushConstantsFromMMIO:skl,bxt */
	whitelist_reg(w, COMMON_SLICE_CHICKEN2);
}