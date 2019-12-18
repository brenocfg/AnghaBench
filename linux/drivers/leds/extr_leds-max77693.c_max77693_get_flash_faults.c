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
typedef  unsigned int u8 ;
struct regmap {int dummy; } ;
struct max77693_sub_led {scalar_t__ fled_id; int /*<<< orphan*/  flash_faults; } ;
struct max77693_led_device {scalar_t__ iout_joint; struct regmap* regmap; } ;

/* Variables and functions */
 unsigned int FLASH_INT_FLED1_OPEN ; 
 unsigned int FLASH_INT_FLED1_SHORT ; 
 unsigned int FLASH_INT_FLED2_OPEN ; 
 unsigned int FLASH_INT_FLED2_SHORT ; 
 unsigned int FLASH_INT_OVER_CURRENT ; 
 scalar_t__ FLED1 ; 
 int /*<<< orphan*/  LED_FAULT_OVER_CURRENT ; 
 int /*<<< orphan*/  LED_FAULT_OVER_VOLTAGE ; 
 int /*<<< orphan*/  LED_FAULT_SHORT_CIRCUIT ; 
 int /*<<< orphan*/  MAX77693_LED_REG_FLASH_INT ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct max77693_led_device* sub_led_to_led (struct max77693_sub_led*) ; 

__attribute__((used)) static int max77693_get_flash_faults(struct max77693_sub_led *sub_led)
{
	struct max77693_led_device *led = sub_led_to_led(sub_led);
	struct regmap *rmap = led->regmap;
	unsigned int v;
	u8 fault_open_mask, fault_short_mask;
	int ret;

	sub_led->flash_faults = 0;

	if (led->iout_joint) {
		fault_open_mask = FLASH_INT_FLED1_OPEN | FLASH_INT_FLED2_OPEN;
		fault_short_mask = FLASH_INT_FLED1_SHORT |
							FLASH_INT_FLED2_SHORT;
	} else {
		fault_open_mask = (sub_led->fled_id == FLED1) ?
						FLASH_INT_FLED1_OPEN :
						FLASH_INT_FLED2_OPEN;
		fault_short_mask = (sub_led->fled_id == FLED1) ?
						FLASH_INT_FLED1_SHORT :
						FLASH_INT_FLED2_SHORT;
	}

	ret = regmap_read(rmap, MAX77693_LED_REG_FLASH_INT, &v);
	if (ret < 0)
		return ret;

	if (v & fault_open_mask)
		sub_led->flash_faults |= LED_FAULT_OVER_VOLTAGE;
	if (v & fault_short_mask)
		sub_led->flash_faults |= LED_FAULT_SHORT_CIRCUIT;
	if (v & FLASH_INT_OVER_CURRENT)
		sub_led->flash_faults |= LED_FAULT_OVER_CURRENT;

	return 0;
}