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
struct intel_engine_cs {scalar_t__ class; struct i915_wa_list whitelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_INVOCATION_COUNT ; 
 scalar_t__ RENDER_CLASS ; 
 int RING_FORCE_TO_NONPRIV_ACCESS_RD ; 
 int RING_FORCE_TO_NONPRIV_RANGE_4 ; 
 int /*<<< orphan*/  gen9_whitelist_build (struct i915_wa_list*) ; 
 int /*<<< orphan*/  whitelist_reg_ext (struct i915_wa_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cfl_whitelist_build(struct intel_engine_cs *engine)
{
	struct i915_wa_list *w = &engine->whitelist;

	if (engine->class != RENDER_CLASS)
		return;

	gen9_whitelist_build(w);

	/*
	 * WaAllowPMDepthAndInvocationCountAccessFromUMD:cfl,whl,cml,aml
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
}