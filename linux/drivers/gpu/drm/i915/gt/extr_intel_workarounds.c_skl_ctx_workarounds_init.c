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
struct intel_engine_cs {int dummy; } ;
struct i915_wa_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen9_ctx_workarounds_init (struct intel_engine_cs*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  skl_tune_iz_hashing (struct intel_engine_cs*,struct i915_wa_list*) ; 

__attribute__((used)) static void skl_ctx_workarounds_init(struct intel_engine_cs *engine,
				     struct i915_wa_list *wal)
{
	gen9_ctx_workarounds_init(engine, wal);
	skl_tune_iz_hashing(engine, wal);
}