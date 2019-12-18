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
struct sh_mobile_lcdc_overlay {int xres_virtual; unsigned long pan_y_offset; unsigned long dma_handle; unsigned long yres_virtual; unsigned long base_addr_y; unsigned long base_addr_c; int /*<<< orphan*/  index; TYPE_2__* channel; TYPE_1__* format; } ;
struct fb_var_screeninfo {int yoffset; int xoffset; } ;
struct fb_info {struct sh_mobile_lcdc_overlay* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  lcdc; } ;
struct TYPE_3__ {int bpp; int /*<<< orphan*/  yuv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDBCR ; 
 int LDBCR_UPC (int /*<<< orphan*/ ) ; 
 int LDBCR_UPD (int /*<<< orphan*/ ) ; 
 int LDBCR_UPF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSACR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSAYR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lcdc_write_overlay (struct sh_mobile_lcdc_overlay*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sh_mobile_lcdc_overlay_pan(struct fb_var_screeninfo *var,
				    struct fb_info *info)
{
	struct sh_mobile_lcdc_overlay *ovl = info->par;
	unsigned long base_addr_y;
	unsigned long base_addr_c;
	unsigned long y_offset;
	unsigned long c_offset;

	if (!ovl->format->yuv) {
		y_offset = (var->yoffset * ovl->xres_virtual + var->xoffset)
			 * ovl->format->bpp / 8;
		c_offset = 0;
	} else {
		unsigned int xsub = ovl->format->bpp < 24 ? 2 : 1;
		unsigned int ysub = ovl->format->bpp < 16 ? 2 : 1;

		y_offset = var->yoffset * ovl->xres_virtual + var->xoffset;
		c_offset = var->yoffset / ysub * ovl->xres_virtual * 2 / xsub
			 + var->xoffset * 2 / xsub;
	}

	/* If the Y offset hasn't changed, the C offset hasn't either. There's
	 * nothing to do in that case.
	 */
	if (y_offset == ovl->pan_y_offset)
		return 0;

	/* Set the source address for the next refresh */
	base_addr_y = ovl->dma_handle + y_offset;
	base_addr_c = ovl->dma_handle + ovl->xres_virtual * ovl->yres_virtual
		    + c_offset;

	ovl->base_addr_y = base_addr_y;
	ovl->base_addr_c = base_addr_c;
	ovl->pan_y_offset = y_offset;

	lcdc_write(ovl->channel->lcdc, LDBCR, LDBCR_UPC(ovl->index));

	lcdc_write_overlay(ovl, LDBnBSAYR(ovl->index), ovl->base_addr_y);
	lcdc_write_overlay(ovl, LDBnBSACR(ovl->index), ovl->base_addr_c);

	lcdc_write(ovl->channel->lcdc, LDBCR,
		   LDBCR_UPF(ovl->index) | LDBCR_UPD(ovl->index));

	return 0;
}