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
typedef  int /*<<< orphan*/  u32 ;
struct i915_wa_list {int dummy; } ;
struct i915_wa {int /*<<< orphan*/  read; int /*<<< orphan*/  val; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  _wa_add (struct i915_wa_list*,struct i915_wa*) ; 

__attribute__((used)) static void
wa_write_masked_or(struct i915_wa_list *wal, i915_reg_t reg, u32 mask,
		   u32 val)
{
	struct i915_wa wa = {
		.reg  = reg,
		.mask = mask,
		.val  = val,
		.read = mask,
	};

	_wa_add(wal, &wa);
}