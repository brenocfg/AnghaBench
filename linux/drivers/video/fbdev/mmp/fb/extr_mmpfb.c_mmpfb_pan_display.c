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
struct mmpfb_info {int /*<<< orphan*/  overlay; scalar_t__ fb_start_dma; } ;
struct mmp_addr {scalar_t__* phys; } ;
struct fb_var_screeninfo {int yoffset; int xres_virtual; int xoffset; int bits_per_pixel; } ;
struct fb_info {struct mmpfb_info* par; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mmp_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmp_overlay_set_addr (int /*<<< orphan*/ ,struct mmp_addr*) ; 

__attribute__((used)) static int mmpfb_pan_display(struct fb_var_screeninfo *var,
		struct fb_info *info)
{
	struct mmpfb_info *fbi = info->par;
	struct mmp_addr addr;

	memset(&addr, 0, sizeof(addr));
	addr.phys[0] = (var->yoffset * var->xres_virtual + var->xoffset)
		* var->bits_per_pixel / 8 + fbi->fb_start_dma;
	mmp_overlay_set_addr(fbi->overlay, &addr);

	return 0;
}