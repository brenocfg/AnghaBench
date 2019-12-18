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
struct lcd_device {int dummy; } ;
struct ams369fg06 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_BLANK_NORMAL ; 
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 int ams369fg06_power (struct ams369fg06*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ams369fg06* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int ams369fg06_set_power(struct lcd_device *ld, int power)
{
	struct ams369fg06 *lcd = lcd_get_data(ld);

	if (power != FB_BLANK_UNBLANK && power != FB_BLANK_POWERDOWN &&
		power != FB_BLANK_NORMAL) {
		dev_err(lcd->dev, "power value should be 0, 1 or 4.\n");
		return -EINVAL;
	}

	return ams369fg06_power(lcd, power);
}