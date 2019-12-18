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
struct lms501kf03 {int power; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 struct lms501kf03* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int lms501kf03_get_power(struct lcd_device *ld)
{
	struct lms501kf03 *lcd = lcd_get_data(ld);

	return lcd->power;
}