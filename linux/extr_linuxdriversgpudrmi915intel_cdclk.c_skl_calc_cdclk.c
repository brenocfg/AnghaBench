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

__attribute__((used)) static int skl_calc_cdclk(int min_cdclk, int vco)
{
	if (vco == 8640000) {
		if (min_cdclk > 540000)
			return 617143;
		else if (min_cdclk > 432000)
			return 540000;
		else if (min_cdclk > 308571)
			return 432000;
		else
			return 308571;
	} else {
		if (min_cdclk > 540000)
			return 675000;
		else if (min_cdclk > 450000)
			return 540000;
		else if (min_cdclk > 337500)
			return 450000;
		else
			return 337500;
	}
}