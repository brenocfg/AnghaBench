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
 unsigned long native_calibrate_cpu_early () ; 
 unsigned long pit_hpet_ptimer_calibrate_cpu () ; 

__attribute__((used)) static unsigned long native_calibrate_cpu(void)
{
	unsigned long tsc_freq = native_calibrate_cpu_early();

	if (!tsc_freq)
		tsc_freq = pit_hpet_ptimer_calibrate_cpu();

	return tsc_freq;
}