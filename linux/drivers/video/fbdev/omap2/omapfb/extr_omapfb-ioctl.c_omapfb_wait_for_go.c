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
struct omapfb_info {int num_overlays; struct omap_overlay** overlays; } ;
struct omap_overlay {int (* wait_for_go ) (struct omap_overlay*) ;} ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int stub1 (struct omap_overlay*) ; 

__attribute__((used)) static int omapfb_wait_for_go(struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	int r = 0;
	int i;

	for (i = 0; i < ofbi->num_overlays; ++i) {
		struct omap_overlay *ovl = ofbi->overlays[i];
		r = ovl->wait_for_go(ovl);
		if (r)
			break;
	}

	return r;
}