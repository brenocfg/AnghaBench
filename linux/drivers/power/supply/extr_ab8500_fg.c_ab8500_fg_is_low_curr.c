#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ab8500_fg {TYPE_2__* bm; } ;
struct TYPE_4__ {TYPE_1__* fg_params; } ;
struct TYPE_3__ {int high_curr_threshold; } ;

/* Variables and functions */

__attribute__((used)) static int ab8500_fg_is_low_curr(struct ab8500_fg *di, int curr)
{
	/*
	 * We want to know if we're in low current mode
	 */
	if (curr > -di->bm->fg_params->high_curr_threshold)
		return true;
	else
		return false;
}