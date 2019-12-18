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
typedef  unsigned int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 time_to_val(unsigned *t, unsigned t_min, unsigned t_step,
							u8 v_min, u8 v_max)
{
	unsigned val;

	val = (*t + t_step / 2 - t_min) / t_step + v_min;

	*t = t_step * (val - v_min) + t_min;

	return (u8)val;
}