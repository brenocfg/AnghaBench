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
struct pm860x_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RGB1_ENABLE ; 
 int /*<<< orphan*/  RGB2_ENABLE ; 
 int pm8606_osc_disable (struct pm860x_chip*,int /*<<< orphan*/ ) ; 
 int pm8606_osc_enable (struct pm860x_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int led_power_set(struct pm860x_chip *chip, int port, int on)
{
	int ret = -EINVAL;

	switch (port) {
	case 0:
	case 1:
	case 2:
		ret = on ? pm8606_osc_enable(chip, RGB1_ENABLE) :
			pm8606_osc_disable(chip, RGB1_ENABLE);
		break;
	case 3:
	case 4:
	case 5:
		ret = on ? pm8606_osc_enable(chip, RGB2_ENABLE) :
			pm8606_osc_disable(chip, RGB2_ENABLE);
		break;
	}
	return ret;
}