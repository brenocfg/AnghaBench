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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int count; TYPE_1__* list; } ;
struct intel_engine_cs {TYPE_2__ whitelist; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ ro_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int whitelist_writable_count(struct intel_engine_cs *engine)
{
	int count = engine->whitelist.count;
	int i;

	for (i = 0; i < engine->whitelist.count; i++) {
		u32 reg = i915_mmio_reg_offset(engine->whitelist.list[i].reg);

		if (ro_register(reg))
			count--;
	}

	return count;
}