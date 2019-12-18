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
struct axp20x_usb_power {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int AXP20X_VBUS_CLIMIT_MASK ; 
 int /*<<< orphan*/  AXP20X_VBUS_IPSOUT_MGMT ; 
#define  AXP813_VBUS_CLIMIT_1500mA 131 
#define  AXP813_VBUS_CLIMIT_2000mA 130 
#define  AXP813_VBUS_CLIMIT_2500mA 129 
#define  AXP813_VBUS_CLIMIT_900mA 128 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp813_get_current_max(struct axp20x_usb_power *power, int *val)
{
	unsigned int v;
	int ret = regmap_read(power->regmap, AXP20X_VBUS_IPSOUT_MGMT, &v);

	if (ret)
		return ret;

	switch (v & AXP20X_VBUS_CLIMIT_MASK) {
	case AXP813_VBUS_CLIMIT_900mA:
		*val = 900000;
		break;
	case AXP813_VBUS_CLIMIT_1500mA:
		*val = 1500000;
		break;
	case AXP813_VBUS_CLIMIT_2000mA:
		*val = 2000000;
		break;
	case AXP813_VBUS_CLIMIT_2500mA:
		*val = 2500000;
		break;
	}
	return 0;
}