#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int frequency; } ;

/* Variables and functions */
 int PPCR ; 
 TYPE_1__* sa11x0_freq_table ; 

unsigned int sa11x0_getspeed(unsigned int cpu)
{
	if (cpu)
		return 0;
	return sa11x0_freq_table[PPCR & 0xf].frequency;
}