#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i915_wa_list {scalar_t__ count; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
struct i915_wa {TYPE_1__ reg; } ;
typedef  TYPE_1__ i915_reg_t ;

/* Variables and functions */
 scalar_t__ GEM_DEBUG_WARN_ON (int) ; 
 scalar_t__ RING_MAX_NONPRIV_SLOTS ; 
 int /*<<< orphan*/  _wa_add (struct i915_wa_list*,struct i915_wa*) ; 
 int /*<<< orphan*/  is_nonpriv_flags_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
whitelist_reg_ext(struct i915_wa_list *wal, i915_reg_t reg, u32 flags)
{
	struct i915_wa wa = {
		.reg = reg
	};

	if (GEM_DEBUG_WARN_ON(wal->count >= RING_MAX_NONPRIV_SLOTS))
		return;

	if (GEM_DEBUG_WARN_ON(!is_nonpriv_flags_valid(flags)))
		return;

	wa.reg.reg |= flags;
	_wa_add(wal, &wa);
}