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
typedef  int u32 ;
struct TYPE_2__ {int bits_per_pixel; int xres_virtual; int yres_virtual; } ;
struct fb_info {TYPE_1__ var; scalar_t__ screen_base; scalar_t__ par; } ;
struct fb_image {int dx; int width; int dy; int height; int depth; char* data; int /*<<< orphan*/  fg_color; int /*<<< orphan*/  bg_color; } ;
struct atafb_par {int next_line; } ;

/* Variables and functions */
 int BYTES_PER_LONG ; 
 int /*<<< orphan*/  atafb_iplan2p2_linefill (struct fb_info*,int,int,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atafb_iplan2p4_linefill (struct fb_info*,int,int,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atafb_iplan2p8_linefill (struct fb_info*,int,int,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atafb_mfb_linefill (struct fb_info*,int,int,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2p_iplan2 (scalar_t__,char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 

__attribute__((used)) static void atafb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct atafb_par *par = (struct atafb_par *)info->par;
	int x2, y2;
	unsigned long *dst;
	int dst_idx;
	const char *src;
	u32 dx, dy, width, height, pitch;

#ifdef ATAFB_FALCON
	if (info->var.bits_per_pixel == 16) {
		cfb_imageblit(info, image);
		return;
	}
#endif

	/*
	 * We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly like we are
	 * doing here.
	 */
	x2 = image->dx + image->width;
	y2 = image->dy + image->height;
	dx = image->dx;
	dy = image->dy;
	x2 = x2 < info->var.xres_virtual ? x2 : info->var.xres_virtual;
	y2 = y2 < info->var.yres_virtual ? y2 : info->var.yres_virtual;
	width = x2 - dx;
	height = y2 - dy;

	if (image->depth == 1) {
		// used for font data
		dst = (unsigned long *)
			((unsigned long)info->screen_base & ~(BYTES_PER_LONG - 1));
		dst_idx = ((unsigned long)info->screen_base & (BYTES_PER_LONG - 1)) * 8;
		dst_idx += dy * par->next_line * 8 + dx;
		src = image->data;
		pitch = (image->width + 7) / 8;
		while (height--) {

			if (info->var.bits_per_pixel == 1)
				atafb_mfb_linefill(info, par->next_line,
						   dy, dx, width, src,
						   image->bg_color, image->fg_color);
			else if (info->var.bits_per_pixel == 2)
				atafb_iplan2p2_linefill(info, par->next_line,
							dy, dx, width, src,
							image->bg_color, image->fg_color);
			else if (info->var.bits_per_pixel == 4)
				atafb_iplan2p4_linefill(info, par->next_line,
							dy, dx, width, src,
							image->bg_color, image->fg_color);
			else
				atafb_iplan2p8_linefill(info, par->next_line,
							dy, dx, width, src,
							image->bg_color, image->fg_color);
			dy++;
			src += pitch;
		}
	} else {
		c2p_iplan2(info->screen_base, image->data, dx, dy, width,
			   height, par->next_line, image->width,
			   info->var.bits_per_pixel);
	}
}