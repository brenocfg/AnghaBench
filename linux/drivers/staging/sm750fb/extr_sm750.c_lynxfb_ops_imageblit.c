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
typedef  unsigned int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  (* de_imageblit ) (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ;} ;
struct sm750_dev {int /*<<< orphan*/  slock; TYPE_4__ accel; } ;
struct TYPE_5__ {unsigned int oScreen; } ;
struct lynxfb_par {TYPE_1__ crtc; struct sm750_dev* dev; } ;
struct TYPE_7__ {unsigned int line_length; scalar_t__ visual; } ;
struct TYPE_6__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_3__ fix; TYPE_2__ var; struct lynxfb_par* par; } ;
struct fb_image {int depth; size_t fg_color; size_t bg_color; int width; int /*<<< orphan*/  height; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  HW_ROP2_COPY ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lynxfb_ops_imageblit(struct fb_info *info,
				 const struct fb_image *image)
{
	unsigned int base, pitch, Bpp;
	unsigned int fgcol, bgcol;
	struct lynxfb_par *par;
	struct sm750_dev *sm750_dev;

	par = info->par;
	sm750_dev = par->dev;
	/*
	 * each time 2d function begin to work,below three variable always need
	 * be set, seems we can put them together in some place
	 */
	base = par->crtc.oScreen;
	pitch = info->fix.line_length;
	Bpp = info->var.bits_per_pixel >> 3;

	/* TODO: Implement hardware acceleration for image->depth > 1 */
	if (image->depth != 1) {
		cfb_imageblit(info, image);
		return;
	}

	if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_DIRECTCOLOR) {
		fgcol = ((u32 *)info->pseudo_palette)[image->fg_color];
		bgcol = ((u32 *)info->pseudo_palette)[image->bg_color];
	} else {
		fgcol = image->fg_color;
		bgcol = image->bg_color;
	}

	/*
	 * If not use spin_lock, system will die if user load driver
	 * and immediately unload driver frequently (dual)
	 * since they fb_count could change during the lifetime of
	 * this lock, we are holding it for all cases.
	 */
	spin_lock(&sm750_dev->slock);

	sm750_dev->accel.de_imageblit(&sm750_dev->accel,
				      image->data, image->width >> 3, 0,
				      base, pitch, Bpp,
				      image->dx, image->dy,
				      image->width, image->height,
				      fgcol, bgcol, HW_ROP2_COPY);
	spin_unlock(&sm750_dev->slock);
}