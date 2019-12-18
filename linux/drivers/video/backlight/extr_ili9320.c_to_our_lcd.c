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
struct ili9320 {int dummy; } ;

/* Variables and functions */
 struct ili9320* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static inline struct ili9320 *to_our_lcd(struct lcd_device *lcd)
{
	return lcd_get_data(lcd);
}