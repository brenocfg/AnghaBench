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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_mocs_table {TYPE_1__* table; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_value; scalar_t__ used; } ;

/* Variables and functions */
 size_t I915_MOCS_PTE ; 

__attribute__((used)) static u32 get_entry_control(const struct drm_i915_mocs_table *table,
			     unsigned int index)
{
	if (table->table[index].used)
		return table->table[index].control_value;

	return table->table[I915_MOCS_PTE].control_value;
}