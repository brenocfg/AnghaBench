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
struct dwc2_hsotg {scalar_t__ vbus_supply; } ;

/* Variables and functions */
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int dwc2_vbus_supply_init(struct dwc2_hsotg *hsotg)
{
	if (hsotg->vbus_supply)
		return regulator_enable(hsotg->vbus_supply);

	return 0;
}