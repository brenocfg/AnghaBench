#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int length; unsigned int offset; } ;
struct TYPE_10__ {int length; unsigned int offset; } ;
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_12__ {TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; scalar_t__ grayscale; } ;
struct TYPE_8__ {scalar_t__ visual; } ;
struct fb_info {TYPE_6__ var; scalar_t__ pseudo_palette; TYPE_2__ fix; } ;
struct au1100fb_device {int /*<<< orphan*/  panel; TYPE_1__* regs; } ;
struct TYPE_7__ {int* lcd_pallettebase; } ;

/* Variables and functions */
 int AU1100_LCD_NBR_PALETTE_ENTRIES ; 
 int EINVAL ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 scalar_t__ panel_is_active (int /*<<< orphan*/ ) ; 
 scalar_t__ panel_is_color (int /*<<< orphan*/ ) ; 
 scalar_t__ panel_swap_rgb (int /*<<< orphan*/ ) ; 
 struct au1100fb_device* to_au1100fb_device (struct fb_info*) ; 

int au1100fb_fb_setcolreg(unsigned regno, unsigned red, unsigned green, unsigned blue, unsigned transp, struct fb_info *fbi)
{
	struct au1100fb_device *fbdev;
	u32 *palette;
	u32 value;

	fbdev = to_au1100fb_device(fbi);
	palette = fbdev->regs->lcd_pallettebase;

	if (regno > (AU1100_LCD_NBR_PALETTE_ENTRIES - 1))
		return -EINVAL;

	if (fbi->var.grayscale) {
		/* Convert color to grayscale */
		red = green = blue =
			(19595 * red + 38470 * green + 7471 * blue) >> 16;
	}

	if (fbi->fix.visual == FB_VISUAL_TRUECOLOR) {
		/* Place color in the pseudopalette */
		if (regno > 16)
			return -EINVAL;

		palette = (u32*)fbi->pseudo_palette;

		red   >>= (16 - fbi->var.red.length);
		green >>= (16 - fbi->var.green.length);
		blue  >>= (16 - fbi->var.blue.length);

		value = (red   << fbi->var.red.offset) 	|
			(green << fbi->var.green.offset)|
			(blue  << fbi->var.blue.offset);
		value &= 0xFFFF;

	} else if (panel_is_active(fbdev->panel)) {
		/* COLOR TFT PALLETTIZED (use RGB 565) */
		value = (red & 0xF800)|((green >> 5) & 0x07E0)|((blue >> 11) & 0x001F);
		value &= 0xFFFF;

	} else if (panel_is_color(fbdev->panel)) {
		/* COLOR STN MODE */
		value = (((panel_swap_rgb(fbdev->panel) ? blue : red) >> 12) & 0x000F) |
			((green >> 8) & 0x00F0) |
			(((panel_swap_rgb(fbdev->panel) ? red : blue) >> 4) & 0x0F00);
		value &= 0xFFF;
	} else {
		/* MONOCHROME MODE */
		value = (green >> 12) & 0x000F;
		value &= 0xF;
	}

	palette[regno] = value;

	return 0;
}