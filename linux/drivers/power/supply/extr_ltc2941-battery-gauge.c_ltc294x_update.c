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
struct ltc294x_info {int charge; int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTC294X_REG_ACC_CHARGE_MSB ; 
 int ltc294x_read_charge_register (struct ltc294x_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltc294x_update(struct ltc294x_info *info)
{
	int charge = ltc294x_read_charge_register(info, LTC294X_REG_ACC_CHARGE_MSB);

	if (charge != info->charge) {
		info->charge = charge;
		power_supply_changed(info->supply);
	}
}