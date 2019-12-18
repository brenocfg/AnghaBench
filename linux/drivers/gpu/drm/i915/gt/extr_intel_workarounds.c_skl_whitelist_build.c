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
 int /*<<< orphan*/  GEN8_L3SQCREG4 ; 
 scalar_t__ RENDER_CLASS ; 
 int /*<<< orphan*/  gen9_whitelist_build (struct i915_wa_list*) ; 
 int /*<<< orphan*/  whitelist_reg (struct i915_wa_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_whitelist_build(struct intel_engine_cs *engine)
{
	struct i915_wa_list *w = &engine->whitelist;

	if (engine->class != RENDER_CLASS)
		return;

	gen9_whitelist_build(w);

	/* WaDisableLSQCROPERFforOCL:skl */
	whitelist_reg(w, GEN8_L3SQCREG4);
}