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
struct intel_gt {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 scalar_t__ HAS_GLOBAL_MOCS_REGISTERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_mocs_init_global (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_mocs_init_l3cc_table (struct intel_gt*) ; 

void intel_mocs_init(struct intel_gt *gt)
{
	intel_mocs_init_l3cc_table(gt);

	if (HAS_GLOBAL_MOCS_REGISTERS(gt->i915))
		intel_mocs_init_global(gt);
}