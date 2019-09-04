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

__attribute__((used)) static int glk_calc_cdclk(int min_cdclk)
{
	if (min_cdclk > 158400)
		return 316800;
	else if (min_cdclk > 79200)
		return 158400;
	else
		return 79200;
}