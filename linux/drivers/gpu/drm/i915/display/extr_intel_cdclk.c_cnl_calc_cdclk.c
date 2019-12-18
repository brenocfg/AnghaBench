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

__attribute__((used)) static int cnl_calc_cdclk(int min_cdclk)
{
	if (min_cdclk > 336000)
		return 528000;
	else if (min_cdclk > 168000)
		return 336000;
	else
		return 168000;
}