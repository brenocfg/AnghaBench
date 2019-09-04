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
 int /*<<< orphan*/  cpu_idle_poll_ctrl (int) ; 

__attribute__((used)) static int omap_pm_prepare(void)
{
	/* We cannot sleep in idle until we have resumed */
	cpu_idle_poll_ctrl(true);
	return 0;
}