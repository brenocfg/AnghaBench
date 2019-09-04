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
struct picolcd_data {struct backlight_device* backlight; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 

void picolcd_exit_backlight(struct picolcd_data *data)
{
	struct backlight_device *bdev = data->backlight;

	data->backlight = NULL;
	backlight_device_unregister(bdev);
}