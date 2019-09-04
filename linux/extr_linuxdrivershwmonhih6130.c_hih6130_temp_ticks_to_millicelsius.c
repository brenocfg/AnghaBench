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

__attribute__((used)) static inline int hih6130_temp_ticks_to_millicelsius(int ticks)
{
	ticks = ticks >> 2;
	/*
	 * from data sheet section 5.0
	 * Formula T = ( ticks / ( 2^14 - 2 ) ) * 165 -40
	 */
	return (DIV_ROUND_CLOSEST(ticks * 1650, 16382) - 400) * 100;
}