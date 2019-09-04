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

__attribute__((used)) static inline int sht21_rh_ticks_to_per_cent_mille(int ticks)
{
	ticks &= ~0x0003; /* clear status bits */
	/*
	 * Formula RH = -6 + 125 * SRH / 2^16 from data sheet 6.1,
	 * optimized for integer fixed point (3 digits) arithmetic
	 */
	return ((15625 * ticks) >> 13) - 6000;
}