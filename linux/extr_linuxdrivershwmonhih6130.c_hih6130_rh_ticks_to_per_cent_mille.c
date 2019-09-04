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
 int DIV_ROUND_CLOSEST (int,int) ; 

__attribute__((used)) static inline int hih6130_rh_ticks_to_per_cent_mille(int ticks)
{
	ticks &= ~0xC000; /* clear status bits */
	/*
	 * from data sheet section 4.0
	 * Formula RH = ( ticks / ( 2^14 -2 ) ) * 100
	 */
	return DIV_ROUND_CLOSEST(ticks * 1000, 16382) * 100;
}