#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ab8500_charger {TYPE_1__* bm; } ;
struct TYPE_2__ {int* chg_input_curr; int n_chg_in_curr; } ;

/* Variables and functions */

__attribute__((used)) static int ab8500_vbus_in_curr_to_regval(struct ab8500_charger *di, int curr)
{
	int i;

	if (curr < di->bm->chg_input_curr[0])
		return 0;

	for (i = 0; i < di->bm->n_chg_in_curr; i++) {
		if (curr < di->bm->chg_input_curr[i])
			return i - 1;
	}

	/* If not last element, return error */
	i = di->bm->n_chg_in_curr - 1;
	if (curr == di->bm->chg_input_curr[i])
		return i;
	else
		return -1;
}