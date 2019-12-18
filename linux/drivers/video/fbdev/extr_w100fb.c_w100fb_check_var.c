#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct w100fb_par {TYPE_2__* mach; } ;
struct TYPE_12__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_11__ {int length; scalar_t__ offset; } ;
struct TYPE_10__ {int offset; int length; } ;
struct TYPE_9__ {int offset; int length; } ;
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; int height; int width; int pixclock; scalar_t__ sync; int /*<<< orphan*/  vmode; scalar_t__ nonstd; TYPE_6__ transp; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; void* yres_virtual; void* xres_virtual; } ;
struct fb_info {struct w100fb_par* par; } ;
struct TYPE_8__ {TYPE_1__* mem; } ;
struct TYPE_7__ {int size; } ;

/* Variables and functions */
 int BITS_PER_PIXEL ; 
 int EINVAL ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int MEM_INT_SIZE ; 
 void* max (void*,int) ; 
 int /*<<< orphan*/  w100fb_get_mode (struct w100fb_par*,int*,int*,int) ; 

__attribute__((used)) static int w100fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct w100fb_par *par=info->par;

	if(!w100fb_get_mode(par, &var->xres, &var->yres, 1))
		return -EINVAL;

	if (par->mach->mem && ((var->xres*var->yres*BITS_PER_PIXEL/8) > (par->mach->mem->size+1)))
		return -EINVAL;

	if (!par->mach->mem && ((var->xres*var->yres*BITS_PER_PIXEL/8) > (MEM_INT_SIZE+1)))
		return -EINVAL;

	var->xres_virtual = max(var->xres_virtual, var->xres);
	var->yres_virtual = max(var->yres_virtual, var->yres);

	if (var->bits_per_pixel > BITS_PER_PIXEL)
		return -EINVAL;
	else
		var->bits_per_pixel = BITS_PER_PIXEL;

	var->red.offset = 11;
	var->red.length = 5;
	var->green.offset = 5;
	var->green.length = 6;
	var->blue.offset = 0;
	var->blue.length = 5;
	var->transp.offset = var->transp.length = 0;

	var->nonstd = 0;
	var->height = -1;
	var->width = -1;
	var->vmode = FB_VMODE_NONINTERLACED;
	var->sync = 0;
	var->pixclock = 0x04;  /* 171521; */

	return 0;
}