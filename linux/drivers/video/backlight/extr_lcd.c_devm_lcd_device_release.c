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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lcd_device_unregister (struct lcd_device*) ; 

__attribute__((used)) static void devm_lcd_device_release(struct device *dev, void *res)
{
	struct lcd_device *lcd = *(struct lcd_device **)res;

	lcd_device_unregister(lcd);
}