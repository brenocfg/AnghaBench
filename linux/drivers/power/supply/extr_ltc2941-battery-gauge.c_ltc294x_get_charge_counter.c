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
struct ltc294x_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ LTC294X_MID_SUPPLY ; 
 int /*<<< orphan*/  LTC294X_REG_ACC_CHARGE_MSB ; 
 int convert_bin_to_uAh (struct ltc294x_info const*,int) ; 
 int ltc294x_read_charge_register (struct ltc294x_info const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc294x_get_charge_counter(
	const struct ltc294x_info *info, int *val)
{
	int value = ltc294x_read_charge_register(info, LTC294X_REG_ACC_CHARGE_MSB);

	if (value < 0)
		return value;
	value -= LTC294X_MID_SUPPLY;
	*val = convert_bin_to_uAh(info, value);
	return 0;
}