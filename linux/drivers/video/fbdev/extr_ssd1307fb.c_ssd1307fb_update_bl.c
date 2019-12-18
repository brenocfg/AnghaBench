#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ssd1307fb_par {int contrast; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int SSD1307FB_CONTRAST ; 
 struct ssd1307fb_par* bl_get_data (struct backlight_device*) ; 
 int ssd1307fb_write_cmd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ssd1307fb_update_bl(struct backlight_device *bdev)
{
	struct ssd1307fb_par *par = bl_get_data(bdev);
	int ret;
	int brightness = bdev->props.brightness;

	par->contrast = brightness;

	ret = ssd1307fb_write_cmd(par->client, SSD1307FB_CONTRAST);
	if (ret < 0)
		return ret;
	ret = ssd1307fb_write_cmd(par->client, par->contrast);
	if (ret < 0)
		return ret;
	return 0;
}