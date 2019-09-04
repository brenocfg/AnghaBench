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
 int EINVAL ; 
 int mx27_cpu_partnumber ; 
 int mx27_cpu_rev ; 
 int mx27_read_cpu_rev () ; 

int mx27_revision(void)
{
	if (mx27_cpu_rev == -1)
		mx27_cpu_rev = mx27_read_cpu_rev();

	if (mx27_cpu_partnumber != 0x8821)
		return -EINVAL;

	return mx27_cpu_rev;
}