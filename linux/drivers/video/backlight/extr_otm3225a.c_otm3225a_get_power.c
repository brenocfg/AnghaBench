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
struct otm3225a_data {int power; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 struct otm3225a_data* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int otm3225a_get_power(struct lcd_device *ld)
{
	struct otm3225a_data *dd = lcd_get_data(ld);

	return dd->power;
}