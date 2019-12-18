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
struct radeonfb_info {TYPE_1__* info; } ;
struct radeon_bl_privdata {int dummy; } ;
struct backlight_device {int dummy; } ;
struct TYPE_2__ {struct backlight_device* bl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 struct radeon_bl_privdata* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  kfree (struct radeon_bl_privdata*) ; 
 int /*<<< orphan*/  printk (char*) ; 

void radeonfb_bl_exit(struct radeonfb_info *rinfo)
{
	struct backlight_device *bd = rinfo->info->bl_dev;

	if (bd) {
		struct radeon_bl_privdata *pdata;

		pdata = bl_get_data(bd);
		backlight_device_unregister(bd);
		kfree(pdata);
		rinfo->info->bl_dev = NULL;

		printk("radeonfb: Backlight unloaded\n");
	}
}