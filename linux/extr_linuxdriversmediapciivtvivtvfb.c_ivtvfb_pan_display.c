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
typedef  int u32 ;
struct TYPE_7__ {int osd_x_pan; int osd_y_pan; int yuv_forced_update; } ;
struct ivtv {TYPE_4__* osd_info; TYPE_3__ yuv_info; } ;
struct fb_var_screeninfo {int yoffset; int xoffset; } ;
struct TYPE_6__ {scalar_t__ yres; scalar_t__ yres_virtual; scalar_t__ xres; scalar_t__ xres_virtual; int bits_per_pixel; } ;
struct TYPE_5__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; scalar_t__ par; } ;
struct TYPE_8__ {int pan_cur; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

__attribute__((used)) static int ivtvfb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	u32 osd_pan_index;
	struct ivtv *itv = (struct ivtv *) info->par;

	if (var->yoffset + info->var.yres > info->var.yres_virtual ||
	    var->xoffset + info->var.xres > info->var.xres_virtual)
		return -EINVAL;

	osd_pan_index = var->yoffset * info->fix.line_length
		      + var->xoffset * info->var.bits_per_pixel / 8;
	write_reg(osd_pan_index, 0x02A0C);

	/* Pass this info back the yuv handler */
	itv->yuv_info.osd_x_pan = var->xoffset;
	itv->yuv_info.osd_y_pan = var->yoffset;
	/* Force update of yuv registers */
	itv->yuv_info.yuv_forced_update = 1;
	/* Remember this value */
	itv->osd_info->pan_cur = osd_pan_index;
	return 0;
}