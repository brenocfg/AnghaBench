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
 int get_loadavg (unsigned long) ; 

__attribute__((used)) static inline int performance_multiplier(unsigned long nr_iowaiters, unsigned long load)
{
	int mult = 1;

	/* for higher loadavg, we are more reluctant */

	mult += 2 * get_loadavg(load);

	/* for IO wait tasks (per cpu!) we add 5x each */
	mult += 10 * nr_iowaiters;

	return mult;
}