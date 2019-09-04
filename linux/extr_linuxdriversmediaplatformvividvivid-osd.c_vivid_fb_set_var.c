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
struct vivid_dev {int display_byte_stride; int bytes_per_pixel; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*) ; 

__attribute__((used)) static int vivid_fb_set_var(struct vivid_dev *dev, struct fb_var_screeninfo *var)
{
	dprintk(dev, 1, "vivid_fb_set_var\n");

	if (var->bits_per_pixel != 16) {
		dprintk(dev, 1, "vivid_fb_set_var - Invalid bpp\n");
		return -EINVAL;
	}
	dev->display_byte_stride = var->xres * dev->bytes_per_pixel;

	return 0;
}