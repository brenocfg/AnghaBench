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
struct tmiofb_par {scalar_t__ lcr; } ;
struct fb_videomode {unsigned int vsync_len; unsigned int upper_margin; unsigned int yres; } ;
struct fb_vblank {unsigned int vcount; int flags; } ;
struct fb_info {struct fb_videomode* mode; struct tmiofb_par* par; } ;

/* Variables and functions */
 int FB_VBLANK_HAVE_VBLANK ; 
 int FB_VBLANK_HAVE_VCOUNT ; 
 int FB_VBLANK_HAVE_VSYNC ; 
 int FB_VBLANK_VBLANKING ; 
 int FB_VBLANK_VSYNCING ; 
 scalar_t__ LCR_CDLN ; 
 unsigned int tmio_ioread16 (scalar_t__) ; 

__attribute__((used)) static int tmiofb_vblank(struct fb_info *fbi, struct fb_vblank *vblank)
{
	struct tmiofb_par *par = fbi->par;
	struct fb_videomode *mode = fbi->mode;
	unsigned int vcount = tmio_ioread16(par->lcr + LCR_CDLN);
	unsigned int vds = mode->vsync_len + mode->upper_margin;

	vblank->vcount = vcount;
	vblank->flags = FB_VBLANK_HAVE_VBLANK | FB_VBLANK_HAVE_VCOUNT
						| FB_VBLANK_HAVE_VSYNC;

	if (vcount < mode->vsync_len)
		vblank->flags |= FB_VBLANK_VSYNCING;

	if (vcount < vds || vcount > vds + mode->yres)
		vblank->flags |= FB_VBLANK_VBLANKING;

	return 0;
}