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
struct intel_uncore {int dummy; } ;
struct i915_wa_list {unsigned int count; int /*<<< orphan*/  name; struct i915_wa* list; } ;
struct i915_wa {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int wa_verify (struct i915_wa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool wa_list_verify(struct intel_uncore *uncore,
			   const struct i915_wa_list *wal,
			   const char *from)
{
	struct i915_wa *wa;
	unsigned int i;
	bool ok = true;

	for (i = 0, wa = wal->list; i < wal->count; i++, wa++)
		ok &= wa_verify(wa,
				intel_uncore_read(uncore, wa->reg),
				wal->name, from);

	return ok;
}