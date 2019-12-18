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
struct TYPE_4__ {unsigned int count; TYPE_1__* list; } ;
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; TYPE_2__ whitelist; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_NOPID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
get_whitelist_reg(const struct intel_engine_cs *engine, unsigned int i)
{
	i915_reg_t reg = i < engine->whitelist.count ?
			 engine->whitelist.list[i].reg :
			 RING_NOPID(engine->mmio_base);

	return i915_mmio_reg_offset(reg);
}