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
struct fb_var_screeninfo {scalar_t__ yres; scalar_t__ yres_virtual; int bits_per_pixel; int xres_virtual; int /*<<< orphan*/  accel_flags; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;
struct atyfb_par {int mmaped; scalar_t__ open; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  aty_disable_irq (struct atyfb_par*) ; 
 struct fb_var_screeninfo default_var ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ noaccel ; 
 int /*<<< orphan*/  wait_for_idle (struct atyfb_par*) ; 

__attribute__((used)) static int atyfb_release(struct fb_info *info, int user)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
#ifdef __sparc__
	int was_mmaped;
#endif

	if (!user)
		return 0;

	par->open--;
	mdelay(1);
	wait_for_idle(par);

	if (par->open)
		return 0;

#ifdef __sparc__
	was_mmaped = par->mmaped;

	par->mmaped = 0;

	if (was_mmaped) {
		struct fb_var_screeninfo var;

		/*
		 * Now reset the default display config, we have
		 * no idea what the program(s) which mmap'd the
		 * chip did to the configuration, nor whether it
		 * restored it correctly.
		 */
		var = default_var;
		if (noaccel)
			var.accel_flags &= ~FB_ACCELF_TEXT;
		else
			var.accel_flags |= FB_ACCELF_TEXT;
		if (var.yres == var.yres_virtual) {
			u32 videoram = (info->fix.smem_len - (PAGE_SIZE << 2));
			var.yres_virtual =
				((videoram * 8) / var.bits_per_pixel) /
				var.xres_virtual;
			if (var.yres_virtual < var.yres)
				var.yres_virtual = var.yres;
		}
	}
#endif
	aty_disable_irq(par);

	return 0;
}