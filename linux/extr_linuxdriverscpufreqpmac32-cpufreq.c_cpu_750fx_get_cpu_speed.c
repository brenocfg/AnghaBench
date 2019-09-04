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
 int HID1_PS ; 
 int /*<<< orphan*/  SPRN_HID1 ; 
 unsigned int hi_freq ; 
 unsigned int low_freq ; 
 int mfspr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cpu_750fx_get_cpu_speed(void)
{
	if (mfspr(SPRN_HID1) & HID1_PS)
		return low_freq;
	else
		return hi_freq;
}