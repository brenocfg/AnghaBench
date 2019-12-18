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
typedef  size_t u32 ;
struct intelfb_info {int depth; size_t* pseudo_palette; int /*<<< orphan*/  pitch; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; } ;
struct fb_image {int depth; size_t fg_color; size_t bg_color; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL (struct intelfb_info*,struct fb_info*) ; 
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 struct intelfb_info* GET_DINFO (struct fb_info*) ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  intelfbhw_do_drawglyph (struct intelfb_info*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intelfb_imageblit(struct fb_info *info,
			      const struct fb_image *image)
{
        struct intelfb_info *dinfo = GET_DINFO(info);
	u32 fgcolor, bgcolor;

#if VERBOSE > 0
	DBG_MSG("intelfb_imageblit\n");
#endif

	if (!ACCEL(dinfo, info) || dinfo->depth == 4
	    || image->depth != 1) {
		cfb_imageblit(info, image);
		return;
	}

	if (dinfo->depth != 8) {
		fgcolor = dinfo->pseudo_palette[image->fg_color];
		bgcolor = dinfo->pseudo_palette[image->bg_color];
	} else {
		fgcolor = image->fg_color;
		bgcolor = image->bg_color;
	}

	if (!intelfbhw_do_drawglyph(dinfo, fgcolor, bgcolor, image->width,
				    image->height, image->data,
				    image->dx, image->dy,
				    dinfo->pitch, info->var.bits_per_pixel)) {
		cfb_imageblit(info, image);
		return;
	}
}