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
struct lv5207lp {TYPE_1__* pdata; } ;
struct fb_info {int /*<<< orphan*/ * dev; } ;
struct backlight_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fbdev; } ;

/* Variables and functions */
 struct lv5207lp* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int lv5207lp_backlight_check_fb(struct backlight_device *backlight,
				       struct fb_info *info)
{
	struct lv5207lp *lv = bl_get_data(backlight);

	return lv->pdata->fbdev == NULL || lv->pdata->fbdev == info->dev;
}