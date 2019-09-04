#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct coverage_entry {int /*<<< orphan*/  matched; int /*<<< orphan*/  regs; TYPE_2__* header; } ;
struct TYPE_8__ {int num_entries; struct coverage_entry* base; } ;
struct TYPE_7__ {int /*<<< orphan*/  bits; } ;
struct TYPE_5__ {int /*<<< orphan*/  bits; } ;
struct TYPE_6__ {TYPE_1__ value; TYPE_3__ mask; } ;

/* Variables and functions */
 TYPE_4__ coverage ; 
 int coverage_fail ; 
 int /*<<< orphan*/  kfree (struct coverage_entry*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void coverage_end(void)
{
	struct coverage_entry *entry = coverage.base;
	struct coverage_entry *end = coverage.base + coverage.num_entries;

	for (; entry < end; ++entry) {
		u32 mask = entry->header->mask.bits;
		u32 value = entry->header->value.bits;

		if (entry->regs) {
			pr_err("FAIL: Register test coverage missing for %08x %08x (%05x)\n",
				mask, value, entry->regs);
			coverage_fail = true;
		}
		if (!entry->matched) {
			pr_err("FAIL: Test coverage entry missing for %08x %08x\n",
				mask, value);
			coverage_fail = true;
		}
	}

	kfree(coverage.base);
}