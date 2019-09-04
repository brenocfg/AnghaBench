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
struct clockdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clkdm_allow_idle (struct clockdomain*) ; 

int omap_pm_clkdms_setup(struct clockdomain *clkdm, void *unused)
{
	clkdm_allow_idle(clkdm);
	return 0;
}