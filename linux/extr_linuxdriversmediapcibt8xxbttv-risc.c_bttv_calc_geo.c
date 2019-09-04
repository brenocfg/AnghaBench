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
typedef  unsigned int u32 ;
struct v4l2_rect {unsigned int left; scalar_t__ top; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_5__ {scalar_t__ top; } ;
struct TYPE_4__ {unsigned int left; scalar_t__ top; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_6__ {TYPE_2__ bounds; TYPE_1__ defrect; } ;
struct bttv_tvnorm {unsigned int swidth; int /*<<< orphan*/  vtotal; TYPE_3__ cropcap; } ;
struct bttv_geometry {unsigned int width; unsigned int hscale; unsigned int hdelay; unsigned int sheight; scalar_t__ vdelay; int vscale; int crop; int vtc; int comb; int /*<<< orphan*/  vtotal; } ;
struct bttv {scalar_t__ input; scalar_t__ dig; scalar_t__ opt_combfilter; } ;

/* Variables and functions */
 int BT848_VSCALE_INT ; 
 scalar_t__ MIN_VDELAY ; 
 int /*<<< orphan*/  bttv_calc_geo_old (struct bttv*,struct bttv_geometry*,unsigned int,unsigned int,int,struct bttv_tvnorm const*) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static void
bttv_calc_geo		(struct bttv *                  btv,
			 struct bttv_geometry *         geo,
			 unsigned int                   width,
			 unsigned int                   height,
			 int                            both_fields,
			 const struct bttv_tvnorm *     tvnorm,
			 const struct v4l2_rect *       crop)
{
	unsigned int c_width;
	unsigned int c_height;
	u32 sr;

	if ((crop->left == tvnorm->cropcap.defrect.left
	     && crop->top == tvnorm->cropcap.defrect.top
	     && crop->width == tvnorm->cropcap.defrect.width
	     && crop->height == tvnorm->cropcap.defrect.height
	     && width <= tvnorm->swidth /* see PAL-Nc et al */)
	    || btv->input == btv->dig) {
		bttv_calc_geo_old(btv, geo, width, height,
				  both_fields, tvnorm);
		return;
	}

	/* For bug compatibility the image size checks permit scale
	   factors > 16. See bttv_crop_calc_limits(). */
	c_width = min((unsigned int) crop->width, width * 16);
	c_height = min((unsigned int) crop->height, height * 16);

	geo->width = width;
	geo->hscale = (c_width * 4096U + (width >> 1)) / width - 4096;
	/* Even to store Cb first, odd for Cr. */
	geo->hdelay = ((crop->left * width + c_width) / c_width) & ~1;

	geo->sheight = c_height;
	geo->vdelay = crop->top - tvnorm->cropcap.bounds.top + MIN_VDELAY;
	sr = c_height >> !both_fields;
	sr = (sr * 512U + (height >> 1)) / height - 512;
	geo->vscale = (0x10000UL - sr) & 0x1fff;
	geo->vscale |= both_fields ? (BT848_VSCALE_INT << 8) : 0;
	geo->vtotal = tvnorm->vtotal;

	geo->crop = (((geo->width   >> 8) & 0x03) |
		     ((geo->hdelay  >> 6) & 0x0c) |
		     ((geo->sheight >> 4) & 0x30) |
		     ((geo->vdelay  >> 2) & 0xc0));

	if (btv->opt_combfilter) {
		geo->vtc  = (width < 193) ? 2 : ((width < 385) ? 1 : 0);
		geo->comb = (width < 769) ? 1 : 0;
	} else {
		geo->vtc  = 0;
		geo->comb = 0;
	}
}