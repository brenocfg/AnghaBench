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
struct hmm_range {int /*<<< orphan*/  pfn_shift; int /*<<< orphan*/  values; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  hmm_range_flags ; 
 int /*<<< orphan*/  hmm_range_values ; 

void amdgpu_hmm_init_range(struct hmm_range *range)
{
	if (range) {
		range->flags = hmm_range_flags;
		range->values = hmm_range_values;
		range->pfn_shift = PAGE_SHIFT;
	}
}