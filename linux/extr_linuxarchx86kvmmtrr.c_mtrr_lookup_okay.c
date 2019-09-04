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
struct mtrr_iter {int mem_type; size_t index; TYPE_2__* range; TYPE_1__* mtrr_state; scalar_t__ fixed; } ;
struct TYPE_4__ {int base; } ;
struct TYPE_3__ {int* fixed_ranges; } ;

/* Variables and functions */

__attribute__((used)) static bool mtrr_lookup_okay(struct mtrr_iter *iter)
{
	if (iter->fixed) {
		iter->mem_type = iter->mtrr_state->fixed_ranges[iter->index];
		return true;
	}

	if (iter->range) {
		iter->mem_type = iter->range->base & 0xff;
		return true;
	}

	return false;
}