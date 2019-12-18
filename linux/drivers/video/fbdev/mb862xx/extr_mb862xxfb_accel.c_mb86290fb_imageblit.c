#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  visual; } ;
struct TYPE_3__ {int xres_virtual; int yres_virtual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ fix; TYPE_1__ var; } ;
struct fb_image {int width; int height; int dx; int dy; int depth; size_t fg_color; size_t bg_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int GDC_ROP_COPY ; 
 int /*<<< orphan*/  GFP_DMA ; 
 void cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 size_t* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 
 void mb86290fb_imageblit1 (size_t*,u16,u16,u16,u16,u16,size_t,size_t,struct fb_image const*,struct fb_info*) ; 
 void mb86290fb_imageblit16 (size_t*,u16,u16,u16,u16,u16,size_t,size_t,struct fb_image const*,struct fb_info*) ; 
 void mb86290fb_imageblit8 (size_t*,u16,u16,u16,u16,u16,size_t,size_t,struct fb_image const*,struct fb_info*) ; 
 int /*<<< orphan*/  mb862xxfb_write_fifo (size_t,size_t*,struct fb_info*) ; 
 int min (int,int) ; 

__attribute__((used)) static void mb86290fb_imageblit(struct fb_info *info,
				const struct fb_image *image)
{
	int mdr;
	u32 *cmd = NULL;
	void (*cmdfn) (u32 *, u16, u16, u16, u16, u16, u32, u32,
		       const struct fb_image *, struct fb_info *) = NULL;
	u32 cmdlen;
	u32 fgcolor = 0, bgcolor = 0;
	u16 step;

	u16 width = image->width, height = image->height;
	u16 dx = image->dx, dy = image->dy;
	int x2, y2, vxres, vyres;

	mdr = (GDC_ROP_COPY << 9);
	x2 = image->dx + image->width;
	y2 = image->dy + image->height;
	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;
	x2 = min(x2, vxres);
	y2 = min(y2, vyres);
	width = x2 - dx;
	height = y2 - dy;

	switch (image->depth) {
	case 1:
		step = (width + 31) >> 5;
		cmdlen = 9 + height * step;
		cmdfn = mb86290fb_imageblit1;
		if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
		    info->fix.visual == FB_VISUAL_DIRECTCOLOR) {
			fgcolor =
			    ((u32 *) (info->pseudo_palette))[image->fg_color];
			bgcolor =
			    ((u32 *) (info->pseudo_palette))[image->bg_color];
		} else {
			fgcolor = image->fg_color;
			bgcolor = image->bg_color;
		}

		break;

	case 8:
		step = (width + 1) >> 1;
		cmdlen = 3 + height * step;
		cmdfn = mb86290fb_imageblit8;
		break;

	case 16:
		step = (width + 1) >> 1;
		cmdlen = 3 + height * step;
		cmdfn = mb86290fb_imageblit16;
		break;

	default:
		cfb_imageblit(info, image);
		return;
	}

	cmd = kmalloc_array(cmdlen, 4, GFP_DMA);
	if (!cmd)
		return cfb_imageblit(info, image);
	cmdfn(cmd, step, dx, dy, width, height, fgcolor, bgcolor, image, info);
	mb862xxfb_write_fifo(cmdlen, cmd, info);
	kfree(cmd);
}