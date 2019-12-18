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
struct axp20x_usb_power {int /*<<< orphan*/  axp20x_id; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  AXP20X_VBUS_CLIMIT_100mA 131 
#define  AXP20X_VBUS_CLIMIT_500mA 130 
#define  AXP20X_VBUS_CLIMIT_900mA 129 
 unsigned int AXP20X_VBUS_CLIMIT_MASK ; 
#define  AXP20X_VBUS_CLIMIT_NONE 128 
 int /*<<< orphan*/  AXP20X_VBUS_IPSOUT_MGMT ; 
 int /*<<< orphan*/  AXP221_ID ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp20x_get_current_max(struct axp20x_usb_power *power, int *val)
{
	unsigned int v;
	int ret = regmap_read(power->regmap, AXP20X_VBUS_IPSOUT_MGMT, &v);

	if (ret)
		return ret;

	switch (v & AXP20X_VBUS_CLIMIT_MASK) {
	case AXP20X_VBUS_CLIMIT_100mA:
		if (power->axp20x_id == AXP221_ID)
			*val = -1; /* No 100mA limit */
		else
			*val = 100000;
		break;
	case AXP20X_VBUS_CLIMIT_500mA:
		*val = 500000;
		break;
	case AXP20X_VBUS_CLIMIT_900mA:
		*val = 900000;
		break;
	case AXP20X_VBUS_CLIMIT_NONE:
		*val = -1;
		break;
	}

	return 0;
}