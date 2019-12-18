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
struct hx8357_data {int state; } ;

/* Variables and functions */
 struct hx8357_data* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int hx8357_get_power(struct lcd_device *lcdev)
{
	struct hx8357_data *lcd = lcd_get_data(lcdev);

	return lcd->state;
}