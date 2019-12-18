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
struct fb_info {int dummy; } ;
struct fb_cmap {unsigned short* red; unsigned short* green; unsigned short* blue; int len; scalar_t__ start; int /*<<< orphan*/ * transp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* blank ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  do_install_cmap (struct fb_info*) ; 
 int /*<<< orphan*/  fb_set_cmap (struct fb_cmap*,struct fb_info*) ; 
 TYPE_1__* fbhw ; 
 int /*<<< orphan*/  memset (unsigned short*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int atafb_blank(int blank, struct fb_info *info)
{
	unsigned short black[16];
	struct fb_cmap cmap;
	if (fbhw->blank && !fbhw->blank(blank))
		return 1;
	if (blank) {
		memset(black, 0, 16 * sizeof(unsigned short));
		cmap.red = black;
		cmap.green = black;
		cmap.blue = black;
		cmap.transp = NULL;
		cmap.start = 0;
		cmap.len = 16;
		fb_set_cmap(&cmap, info);
	}
#if 0
	else
		do_install_cmap(info);
#endif
	return 0;
}