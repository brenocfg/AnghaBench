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
struct picolcd_data {int lcd_contrast; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 struct picolcd_data* lcd_get_data (struct lcd_device*) ; 

__attribute__((used)) static int picolcd_get_contrast(struct lcd_device *ldev)
{
	struct picolcd_data *data = lcd_get_data(ldev);
	return data->lcd_contrast;
}