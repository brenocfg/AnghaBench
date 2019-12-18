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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fb_videomode {int /*<<< orphan*/  name; } ;
struct da8xx_lcdc_platform_data {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fb_videomode*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct da8xx_lcdc_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct fb_videomode* known_lcd_panels ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fb_videomode *da8xx_fb_get_videomode(struct platform_device *dev)
{
	struct da8xx_lcdc_platform_data *fb_pdata = dev_get_platdata(&dev->dev);
	struct fb_videomode *lcdc_info;
	int i;

	for (i = 0, lcdc_info = known_lcd_panels;
		i < ARRAY_SIZE(known_lcd_panels); i++, lcdc_info++) {
		if (strcmp(fb_pdata->type, lcdc_info->name) == 0)
			break;
	}

	if (i == ARRAY_SIZE(known_lcd_panels)) {
		dev_err(&dev->dev, "no panel found\n");
		return NULL;
	}
	dev_info(&dev->dev, "found %s panel\n", lcdc_info->name);

	return lcdc_info;
}