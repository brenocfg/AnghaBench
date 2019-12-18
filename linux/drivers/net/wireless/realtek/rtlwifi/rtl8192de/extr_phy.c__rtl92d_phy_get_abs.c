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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static u32 _rtl92d_phy_get_abs(u32 val1, u32 val2)
{
	u32 ret;

	if (val1 >= val2)
		ret = val1 - val2;
	else
		ret = val2 - val1;
	return ret;
}