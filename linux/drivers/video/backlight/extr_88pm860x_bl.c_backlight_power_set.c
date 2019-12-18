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
 int /*<<< orphan*/  WLED1_DUTY ; 
 int /*<<< orphan*/  WLED2_DUTY ; 
 int /*<<< orphan*/  WLED3_DUTY ; 
 int pm8606_osc_disable (struct pm860x_chip*,int /*<<< orphan*/ ) ; 
 int pm8606_osc_enable (struct pm860x_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int backlight_power_set(struct pm860x_chip *chip, int port,
		int on)
{
	int ret = -EINVAL;

	switch (port) {
	case 0:
		ret = on ? pm8606_osc_enable(chip, WLED1_DUTY) :
			pm8606_osc_disable(chip, WLED1_DUTY);
		break;
	case 1:
		ret = on ? pm8606_osc_enable(chip, WLED2_DUTY) :
			pm8606_osc_disable(chip, WLED2_DUTY);
		break;
	case 2:
		ret = on ? pm8606_osc_enable(chip, WLED3_DUTY) :
			pm8606_osc_disable(chip, WLED3_DUTY);
		break;
	}
	return ret;
}