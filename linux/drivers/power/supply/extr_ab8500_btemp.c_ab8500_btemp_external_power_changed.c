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
struct ab8500_btemp {int /*<<< orphan*/  btemp_psy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ab8500_btemp_get_ext_psy_data ; 
 int /*<<< orphan*/  class_for_each_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_class ; 
 struct ab8500_btemp* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static void ab8500_btemp_external_power_changed(struct power_supply *psy)
{
	struct ab8500_btemp *di = power_supply_get_drvdata(psy);

	class_for_each_device(power_supply_class, NULL,
		di->btemp_psy, ab8500_btemp_get_ext_psy_data);
}