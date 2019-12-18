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
typedef  int u16 ;

/* Variables and functions */
 int temp_decay_factor ; 

__attribute__((used)) static u16 update_average_temp(u16 avg, u16 val)
{
	u16 ret;

	/* Multiply by 100 for extra precision */
	ret = (val * 100 / temp_decay_factor) +
		(((temp_decay_factor - 1) * avg) / temp_decay_factor);
	return ret;
}