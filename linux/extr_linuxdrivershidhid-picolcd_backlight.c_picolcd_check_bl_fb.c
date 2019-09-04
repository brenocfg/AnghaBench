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
struct picolcd_data {int dummy; } ;
struct fb_info {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ bl_get_data (struct backlight_device*) ; 
 struct fb_info* picolcd_fbinfo (struct picolcd_data*) ; 

__attribute__((used)) static int picolcd_check_bl_fb(struct backlight_device *bdev, struct fb_info *fb)
{
	return fb && fb == picolcd_fbinfo((struct picolcd_data *)bl_get_data(bdev));
}