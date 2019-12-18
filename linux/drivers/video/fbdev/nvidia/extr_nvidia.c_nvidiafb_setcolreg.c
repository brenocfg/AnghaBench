#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct nvidia_par {int dummy; } ;
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_8__ {unsigned int offset; } ;
struct TYPE_7__ {unsigned int offset; } ;
struct TYPE_10__ {int bits_per_pixel; TYPE_4__ green; TYPE_3__ blue; TYPE_2__ red; scalar_t__ grayscale; } ;
struct TYPE_6__ {scalar_t__ visual; } ;
struct fb_info {TYPE_5__ var; scalar_t__ pseudo_palette; TYPE_1__ fix; struct nvidia_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  nvidia_read_clut (struct nvidia_par*,unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  nvidia_write_clut (struct nvidia_par*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int nvidiafb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp,
			      struct fb_info *info)
{
	struct nvidia_par *par = info->par;
	int i;

	NVTRACE_ENTER();
	if (regno >= (1 << info->var.green.length))
		return -EINVAL;

	if (info->var.grayscale) {
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}

	if (regno < 16 && info->fix.visual == FB_VISUAL_DIRECTCOLOR) {
		((u32 *) info->pseudo_palette)[regno] =
		    (regno << info->var.red.offset) |
		    (regno << info->var.green.offset) |
		    (regno << info->var.blue.offset);
	}

	switch (info->var.bits_per_pixel) {
	case 8:
		/* "transparent" stuff is completely ignored. */
		nvidia_write_clut(par, regno, red >> 8, green >> 8, blue >> 8);
		break;
	case 16:
		if (info->var.green.length == 5) {
			for (i = 0; i < 8; i++) {
				nvidia_write_clut(par, regno * 8 + i, red >> 8,
						  green >> 8, blue >> 8);
			}
		} else {
			u8 r, g, b;

			if (regno < 32) {
				for (i = 0; i < 8; i++) {
					nvidia_write_clut(par, regno * 8 + i,
							  red >> 8, green >> 8,
							  blue >> 8);
				}
			}

			nvidia_read_clut(par, regno * 4, &r, &g, &b);

			for (i = 0; i < 4; i++)
				nvidia_write_clut(par, regno * 4 + i, r,
						  green >> 8, b);
		}
		break;
	case 32:
		nvidia_write_clut(par, regno, red >> 8, green >> 8, blue >> 8);
		break;
	default:
		/* do nothing */
		break;
	}

	NVTRACE_LEAVE();
	return 0;
}