#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_8__ {struct drm_framebuffer* fb; } ;
struct psb_fbdev {TYPE_1__ psb_fb_helper; } ;
struct TYPE_12__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_9__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_6__ var; struct psb_fbdev* par; } ;
struct drm_framebuffer {TYPE_7__* format; } ;
struct TYPE_14__ {int* cpp; } ;

/* Variables and functions */
 unsigned int CMAP_TOHW (unsigned int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 

__attribute__((used)) static int psbfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	struct psb_fbdev *fbdev = info->par;
	struct drm_framebuffer *fb = fbdev->psb_fb_helper.fb;
	uint32_t v;

	if (!fb)
		return -ENOMEM;

	if (regno > 255)
		return 1;

	red = CMAP_TOHW(red, info->var.red.length);
	blue = CMAP_TOHW(blue, info->var.blue.length);
	green = CMAP_TOHW(green, info->var.green.length);
	transp = CMAP_TOHW(transp, info->var.transp.length);

	v = (red << info->var.red.offset) |
	    (green << info->var.green.offset) |
	    (blue << info->var.blue.offset) |
	    (transp << info->var.transp.offset);

	if (regno < 16) {
		switch (fb->format->cpp[0] * 8) {
		case 16:
			((uint32_t *) info->pseudo_palette)[regno] = v;
			break;
		case 24:
		case 32:
			((uint32_t *) info->pseudo_palette)[regno] = v;
			break;
		}
	}

	return 0;
}