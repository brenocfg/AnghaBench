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
 int HZ ; 
 int loops_per_jiffy ; 
 int thread_freq_mhz ; 

void calibrate_delay(void)
{
	loops_per_jiffy = thread_freq_mhz * 1000000 / HZ;
}