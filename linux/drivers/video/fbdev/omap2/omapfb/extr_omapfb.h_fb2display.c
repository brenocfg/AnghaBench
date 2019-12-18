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
struct omapfb_info {scalar_t__ num_overlays; struct omap_overlay** overlays; } ;
struct omap_overlay {struct omap_dss_device* (* get_device ) (struct omap_overlay*) ;} ;
struct omap_dss_device {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 struct omap_dss_device* stub1 (struct omap_overlay*) ; 

__attribute__((used)) static inline struct omap_dss_device *fb2display(struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omap_overlay *ovl;

	/* XXX: returns the display connected to first attached overlay */

	if (ofbi->num_overlays == 0)
		return NULL;

	ovl = ofbi->overlays[0];

	return ovl->get_device(ovl);
}