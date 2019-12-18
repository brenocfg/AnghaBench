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
struct fb_info {int /*<<< orphan*/ * dev; } ;
struct bd6107 {TYPE_1__* pdata; } ;
struct backlight_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fbdev; } ;

/* Variables and functions */
 struct bd6107* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int bd6107_backlight_check_fb(struct backlight_device *backlight,
				       struct fb_info *info)
{
	struct bd6107 *bd = bl_get_data(backlight);

	return bd->pdata->fbdev == NULL || bd->pdata->fbdev == info->dev;
}