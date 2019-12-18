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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 egress_cycles(u32 len, u32 rate)
{
	u32 cycles;

	/*
	 * cycles is:
	 *
	 *          (length) [bits] / (rate) [bits/sec]
	 *  ---------------------------------------------------
	 *  fabric_clock_period == 1 /(805 * 10^6) [cycles/sec]
	 */

	cycles = len * 8; /* bits */
	cycles *= 805;
	cycles /= rate;

	return cycles;
}