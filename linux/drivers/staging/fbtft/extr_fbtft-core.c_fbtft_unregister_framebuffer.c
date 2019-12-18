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
struct TYPE_2__ {int /*<<< orphan*/  (* unregister_backlight ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;
struct fb_info {struct fbtft_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbtft_sysfs_exit (struct fbtft_par*) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

int fbtft_unregister_framebuffer(struct fb_info *fb_info)
{
	struct fbtft_par *par = fb_info->par;

	if (par->fbtftops.unregister_backlight)
		par->fbtftops.unregister_backlight(par);
	fbtft_sysfs_exit(par);
	unregister_framebuffer(fb_info);

	return 0;
}