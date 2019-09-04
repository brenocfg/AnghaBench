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
 int ERANGE ; 
 int /*<<< orphan*/  MAX44000_LED_CURRENT_MASK ; 
 int MAX44000_LED_CURRENT_MAX ; 
 int /*<<< orphan*/  MAX44000_REG_CFG_TX ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max44000_write_led_current_raw(struct max44000_data *data, int val)
{
	/* Maybe we should clamp the value instead? */
	if (val < 0 || val > MAX44000_LED_CURRENT_MAX)
		return -ERANGE;
	if (val >= 8)
		val += 4;
	return regmap_write_bits(data->regmap, MAX44000_REG_CFG_TX,
				 MAX44000_LED_CURRENT_MASK, val);
}