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
struct lcd_device {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ lcd_get_data (struct lcd_device*) ; 
 struct fb_info* picolcd_fbinfo (struct picolcd_data*) ; 

__attribute__((used)) static int picolcd_check_lcd_fb(struct lcd_device *ldev, struct fb_info *fb)
{
	return fb && fb == picolcd_fbinfo((struct picolcd_data *)lcd_get_data(ldev));
}