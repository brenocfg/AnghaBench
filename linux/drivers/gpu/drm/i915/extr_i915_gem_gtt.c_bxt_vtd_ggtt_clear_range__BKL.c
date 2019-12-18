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
typedef  int /*<<< orphan*/  u64 ;
struct i915_address_space {int dummy; } ;
struct clear_range {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; struct i915_address_space* member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_vtd_ggtt_clear_range__cb ; 
 int /*<<< orphan*/  stop_machine (int /*<<< orphan*/ ,struct clear_range*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bxt_vtd_ggtt_clear_range__BKL(struct i915_address_space *vm,
					  u64 start,
					  u64 length)
{
	struct clear_range arg = { vm, start, length };

	stop_machine(bxt_vtd_ggtt_clear_range__cb, &arg, NULL);
}