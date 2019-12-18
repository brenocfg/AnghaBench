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
struct mx3fb_data {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct mx3fb_data* bl_get_data (struct backlight_device*) ; 
 int sdc_get_brightness (struct mx3fb_data*) ; 

__attribute__((used)) static int mx3fb_bl_get_brightness(struct backlight_device *bl)
{
	struct mx3fb_data *fbd = bl_get_data(bl);

	return sdc_get_brightness(fbd);
}