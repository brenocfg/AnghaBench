#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct fb_info {scalar_t__ pseudo_palette; struct fb_var_screeninfo var; } ;
typedef  enum omapfb_color_format { ____Placeholder_omapfb_color_format } omapfb_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  OMAPFB_COLOR_CLUT_1BPP 138 
#define  OMAPFB_COLOR_CLUT_2BPP 137 
#define  OMAPFB_COLOR_CLUT_4BPP 136 
#define  OMAPFB_COLOR_CLUT_8BPP 135 
#define  OMAPFB_COLOR_RGB24P 134 
#define  OMAPFB_COLOR_RGB24U 133 
#define  OMAPFB_COLOR_RGB444 132 
#define  OMAPFB_COLOR_RGB565 131 
#define  OMAPFB_COLOR_YUV420 130 
#define  OMAPFB_COLOR_YUV422 129 
#define  OMAPFB_COLOR_YUY422 128 

__attribute__((used)) static int _setcolreg(struct fb_info *fbi, u_int regno, u_int red, u_int green,
		u_int blue, u_int transp, int update_hw_pal)
{
	/*struct omapfb_info *ofbi = FB2OFB(fbi);*/
	/*struct omapfb2_device *fbdev = ofbi->fbdev;*/
	struct fb_var_screeninfo *var = &fbi->var;
	int r = 0;

	enum omapfb_color_format mode = OMAPFB_COLOR_RGB24U; /* XXX */

	/*switch (plane->color_mode) {*/
	switch (mode) {
	case OMAPFB_COLOR_YUV422:
	case OMAPFB_COLOR_YUV420:
	case OMAPFB_COLOR_YUY422:
		r = -EINVAL;
		break;
	case OMAPFB_COLOR_CLUT_8BPP:
	case OMAPFB_COLOR_CLUT_4BPP:
	case OMAPFB_COLOR_CLUT_2BPP:
	case OMAPFB_COLOR_CLUT_1BPP:
		/*
		   if (fbdev->ctrl->setcolreg)
		   r = fbdev->ctrl->setcolreg(regno, red, green, blue,
		   transp, update_hw_pal);
		   */
		/* Fallthrough */
		r = -EINVAL;
		break;
	case OMAPFB_COLOR_RGB565:
	case OMAPFB_COLOR_RGB444:
	case OMAPFB_COLOR_RGB24P:
	case OMAPFB_COLOR_RGB24U:
		if (r != 0)
			break;

		if (regno < 16) {
			u32 pal;
			pal = ((red >> (16 - var->red.length)) <<
					var->red.offset) |
				((green >> (16 - var->green.length)) <<
				 var->green.offset) |
				(blue >> (16 - var->blue.length));
			((u32 *)(fbi->pseudo_palette))[regno] = pal;
		}
		break;
	default:
		BUG();
	}
	return r;
}