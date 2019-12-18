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
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hw_wait_phy_stable(void)
{
	/*
	 * The phy needs some delay to output the stable status from low
	 * power mode. And for OTGSC, the status inputs are debounced
	 * using a 1 ms time constant, so, delay 2ms for controller to get
	 * the stable status, like vbus and id when the phy leaves low power.
	 */
	usleep_range(2000, 2500);
}