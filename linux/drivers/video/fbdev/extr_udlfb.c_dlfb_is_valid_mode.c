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
struct fb_videomode {int xres; int yres; } ;
struct dlfb_data {int sku_pixel_limit; } ;

/* Variables and functions */

__attribute__((used)) static int dlfb_is_valid_mode(struct fb_videomode *mode, struct dlfb_data *dlfb)
{
	if (mode->xres * mode->yres > dlfb->sku_pixel_limit)
		return 0;

	return 1;
}