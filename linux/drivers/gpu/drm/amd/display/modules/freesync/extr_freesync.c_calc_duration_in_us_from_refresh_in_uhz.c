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

/* Variables and functions */
 scalar_t__ div64_u64 (unsigned long long,unsigned int) ; 

__attribute__((used)) static unsigned int calc_duration_in_us_from_refresh_in_uhz(
		unsigned int refresh_in_uhz)
{
	unsigned int duration_in_us =
			((unsigned int)(div64_u64((1000000000ULL * 1000),
					refresh_in_uhz)));
	return duration_in_us;
}