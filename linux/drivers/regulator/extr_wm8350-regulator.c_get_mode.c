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
struct wm8350_dcdc_efficiency {int uA_load_min; int uA_load_max; unsigned int mode; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_NORMAL ; 

__attribute__((used)) static unsigned int get_mode(int uA, const struct wm8350_dcdc_efficiency *eff)
{
	int i = 0;

	while (eff[i].uA_load_min != -1) {
		if (uA >= eff[i].uA_load_min && uA <= eff[i].uA_load_max)
			return eff[i].mode;
		i++;
	}
	return REGULATOR_MODE_NORMAL;
}