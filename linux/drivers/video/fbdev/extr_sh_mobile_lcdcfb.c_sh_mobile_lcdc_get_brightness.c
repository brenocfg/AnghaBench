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
struct sh_mobile_lcdc_chan {int bl_brightness; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct sh_mobile_lcdc_chan* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int sh_mobile_lcdc_get_brightness(struct backlight_device *bdev)
{
	struct sh_mobile_lcdc_chan *ch = bl_get_data(bdev);

	return ch->bl_brightness;
}