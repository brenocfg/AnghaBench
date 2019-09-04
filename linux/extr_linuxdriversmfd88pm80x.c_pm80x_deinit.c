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
struct TYPE_2__ {int /*<<< orphan*/ * companion; } ;

/* Variables and functions */
 TYPE_1__* g_pm80x_chip ; 

int pm80x_deinit(void)
{
	/*
	 * workaround: clear the dependency between pm800 and pm805.
	 * would remove it after HW chip fixes the issue.
	 */
	if (g_pm80x_chip->companion)
		g_pm80x_chip->companion = NULL;
	else
		g_pm80x_chip = NULL;
	return 0;
}