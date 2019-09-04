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

__attribute__((used)) static int bxt_calc_cdclk(int min_cdclk)
{
	if (min_cdclk > 576000)
		return 624000;
	else if (min_cdclk > 384000)
		return 576000;
	else if (min_cdclk > 288000)
		return 384000;
	else if (min_cdclk > 144000)
		return 288000;
	else
		return 144000;
}