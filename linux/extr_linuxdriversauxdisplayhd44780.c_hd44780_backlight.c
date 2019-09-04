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
struct hd44780 {scalar_t__* pins; } ;
struct charlcd {struct hd44780* drvdata; } ;

/* Variables and functions */
 size_t PIN_CTRL_BL ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 

__attribute__((used)) static void hd44780_backlight(struct charlcd *lcd, int on)
{
	struct hd44780 *hd = lcd->drvdata;

	if (hd->pins[PIN_CTRL_BL])
		gpiod_set_value_cansleep(hd->pins[PIN_CTRL_BL], on);
}