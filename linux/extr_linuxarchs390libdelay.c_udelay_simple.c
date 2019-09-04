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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ get_tod_clock_fast () ; 

void udelay_simple(unsigned long long usecs)
{
	u64 end;

	end = get_tod_clock_fast() + (usecs << 12);
	while (get_tod_clock_fast() < end)
		cpu_relax();
}