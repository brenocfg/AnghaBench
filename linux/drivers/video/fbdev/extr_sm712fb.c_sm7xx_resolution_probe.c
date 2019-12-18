#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smtcfb_info {TYPE_2__* fb; } ;
struct TYPE_6__ {scalar_t__ lfb_width; int /*<<< orphan*/  lfb_depth; int /*<<< orphan*/  lfb_height; } ;
struct TYPE_4__ {scalar_t__ xres; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres; } ;
struct TYPE_5__ {TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCREEN_BPP ; 
 scalar_t__ SCREEN_X_RES ; 
 int /*<<< orphan*/  SCREEN_Y_RES_NETBOOK ; 
 int /*<<< orphan*/  SCREEN_Y_RES_PC ; 
 int /*<<< orphan*/  big_pixel_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ smtc_scr_info ; 

__attribute__((used)) static void sm7xx_resolution_probe(struct smtcfb_info *sfb)
{
	/* get mode parameter from smtc_scr_info */
	if (smtc_scr_info.lfb_width != 0) {
		sfb->fb->var.xres = smtc_scr_info.lfb_width;
		sfb->fb->var.yres = smtc_scr_info.lfb_height;
		sfb->fb->var.bits_per_pixel = smtc_scr_info.lfb_depth;
		goto final;
	}

	/*
	 * No parameter, default resolution is 1024x768-16.
	 *
	 * FIXME: earlier laptops, such as IBM Thinkpad 240X, has a 800x600
	 * panel, also see the comments about Thinkpad 240X above.
	 */
	sfb->fb->var.xres = SCREEN_X_RES;
	sfb->fb->var.yres = SCREEN_Y_RES_PC;
	sfb->fb->var.bits_per_pixel = SCREEN_BPP;

#ifdef CONFIG_MIPS
	/*
	 * Loongson MIPS netbooks use 1024x600 LCD panels, which is the original
	 * target platform of this driver, but nearly all old x86 laptops have
	 * 1024x768. Lighting 768 panels using 600's timings would partially
	 * garble the display, so we don't want that. But it's not possible to
	 * distinguish them reliably.
	 *
	 * So we change the default to 768, but keep 600 as-is on MIPS.
	 */
	sfb->fb->var.yres = SCREEN_Y_RES_NETBOOK;
#endif

final:
	big_pixel_depth(sfb->fb->var.bits_per_pixel, smtc_scr_info.lfb_depth);
}