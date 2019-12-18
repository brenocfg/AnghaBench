#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tmio_fb_data {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct fb_videomode {int xres; } ;
struct TYPE_8__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct TYPE_6__ {int offset; int length; } ;
struct TYPE_5__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; int yres_virtual; int yres; scalar_t__ rotate; int /*<<< orphan*/  width; int /*<<< orphan*/  height; scalar_t__ nonstd; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; scalar_t__ grayscale; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct fb_info {int screen_size; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 struct tmio_fb_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode*) ; 
 struct fb_videomode* tmiofb_find_mode (struct fb_info*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int tmiofb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{

	struct fb_videomode *mode;
	struct tmio_fb_data *data = dev_get_platdata(info->device);

	mode = tmiofb_find_mode(info, var);
	if (!mode || var->bits_per_pixel > 16)
		return -EINVAL;

	fb_videomode_to_var(var, mode);

	var->xres_virtual = mode->xres;
	var->yres_virtual = info->screen_size / (mode->xres * 2);

	if (var->yres_virtual < var->yres)
		return -EINVAL;

	var->xoffset = 0;
	var->yoffset = 0;
	var->bits_per_pixel = 16;
	var->grayscale = 0;
	var->red.offset = 11;
	var->red.length = 5;
	var->green.offset = 5;
	var->green.length = 6;
	var->blue.offset = 0;
	var->blue.length = 5;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->nonstd = 0;
	var->height = data->height; /* mm */
	var->width = data->width; /* mm */
	var->rotate = 0;
	return 0;
}