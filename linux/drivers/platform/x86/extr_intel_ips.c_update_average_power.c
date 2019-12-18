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
typedef  int u16 ;

/* Variables and functions */
 int power_decay_factor ; 

__attribute__((used)) static u16 update_average_power(u32 avg, u32 val)
{
	u32 ret;

	ret = (val / power_decay_factor) +
		(((power_decay_factor - 1) * avg) / power_decay_factor);

	return ret;
}