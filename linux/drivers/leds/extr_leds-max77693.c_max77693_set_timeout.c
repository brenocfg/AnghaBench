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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct max77693_led_device {int /*<<< orphan*/  current_flash_timeout; struct regmap* regmap; } ;

/* Variables and functions */
 int FLASH_TMR_LEVEL ; 
 int /*<<< orphan*/  MAX77693_LED_REG_FLASH_TIMER ; 
 int max77693_flash_timeout_to_reg (int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_set_timeout(struct max77693_led_device *led, u32 microsec)
{
	struct regmap *rmap = led->regmap;
	u8 v;
	int ret;

	v = max77693_flash_timeout_to_reg(microsec) | FLASH_TMR_LEVEL;

	ret = regmap_write(rmap, MAX77693_LED_REG_FLASH_TIMER, v);
	if (ret < 0)
		return ret;

	led->current_flash_timeout = microsec;

	return 0;
}