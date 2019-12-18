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
typedef  unsigned int u32 ;
struct TYPE_2__ {scalar_t__ grayscale; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_1__ var; } ;

/* Variables and functions */
 unsigned int BLUE_SHIFT ; 
 int EINVAL ; 
 unsigned int GREEN_SHIFT ; 
 unsigned int PALETTE_ENTRIES_NO ; 
 unsigned int RED_SHIFT ; 

__attribute__((used)) static int
xilinx_fb_setcolreg(unsigned int regno, unsigned int red, unsigned int green,
		    unsigned int blue, unsigned int transp, struct fb_info *fbi)
{
	u32 *palette = fbi->pseudo_palette;

	if (regno >= PALETTE_ENTRIES_NO)
		return -EINVAL;

	if (fbi->var.grayscale) {
		/* Convert color to grayscale.
		 * grayscale = 0.30*R + 0.59*G + 0.11*B
		 */
		blue = (red * 77 + green * 151 + blue * 28 + 127) >> 8;
		green = blue;
		red = green;
	}

	/* fbi->fix.visual is always FB_VISUAL_TRUECOLOR */

	/* We only handle 8 bits of each color. */
	red >>= 8;
	green >>= 8;
	blue >>= 8;
	palette[regno] = (red << RED_SHIFT) | (green << GREEN_SHIFT) |
			 (blue << BLUE_SHIFT);

	return 0;
}