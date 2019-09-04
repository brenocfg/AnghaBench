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
typedef  scalar_t__ u32 ;
struct amdgpu_clock_array {unsigned int count; scalar_t__* values; } ;

/* Variables and functions */

__attribute__((used)) static u32 btc_find_valid_clock(struct amdgpu_clock_array *clocks,
		                u32 max_clock, u32 requested_clock)
{
	unsigned int i;

	if ((clocks == NULL) || (clocks->count == 0))
		return (requested_clock < max_clock) ? requested_clock : max_clock;

	for (i = 0; i < clocks->count; i++) {
		if (clocks->values[i] >= requested_clock)
			return (clocks->values[i] < max_clock) ? clocks->values[i] : max_clock;
	}

	return (clocks->values[clocks->count - 1] < max_clock) ?
		clocks->values[clocks->count - 1] : max_clock;
}