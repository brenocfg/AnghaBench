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
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int pd_power_on(struct generic_pm_domain *domain)
{
	/*
	 * Handle the ungating of the PM domain regulator here.
	 *
	 * Drivers/subsystems handling devices in the PM domain needs to perform
	 * register context save/restore from their respective runtime PM
	 * callbacks, to be able to enable PM domain gating/ungating.
	 */
	return 0;
}