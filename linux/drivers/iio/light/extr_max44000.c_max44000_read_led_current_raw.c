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
struct max44000_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int MAX44000_LED_CURRENT_MASK ; 
 int /*<<< orphan*/  MAX44000_REG_CFG_TX ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max44000_read_led_current_raw(struct max44000_data *data)
{
	unsigned int regval;
	int ret;

	ret = regmap_read(data->regmap, MAX44000_REG_CFG_TX, &regval);
	if (ret < 0)
		return ret;
	regval &= MAX44000_LED_CURRENT_MASK;
	if (regval >= 8)
		regval -= 4;
	return regval;
}