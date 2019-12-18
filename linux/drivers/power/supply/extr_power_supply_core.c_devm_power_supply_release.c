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
struct power_supply {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_supply_unregister (struct power_supply*) ; 

__attribute__((used)) static void devm_power_supply_release(struct device *dev, void *res)
{
	struct power_supply **psy = res;

	power_supply_unregister(*psy);
}