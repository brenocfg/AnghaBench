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
 int EINVAL ; 

__attribute__((used)) static int vadc_hw_settle_time_from_dt(u32 value)
{
	if ((value <= 1000 && value % 100) || (value > 1000 && value % 2000))
		return -EINVAL;

	if (value <= 1000)
		value /= 100;
	else
		value = value / 2000 + 10;

	return value;
}