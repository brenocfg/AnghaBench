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
 unsigned long NDELAY_MULT ; 
 unsigned long long NDELAY_SHIFT ; 
 int /*<<< orphan*/  __delay (unsigned long long) ; 
 unsigned long lpj_fine ; 

void ndelay(unsigned long nsecs)
{
	/*
	 * This doesn't bother checking for overflow, as it won't happen (it's
	 * an hour) of delay.
	 */
	unsigned long long ncycles = nsecs * lpj_fine * NDELAY_MULT;
	__delay(ncycles >> NDELAY_SHIFT);
}