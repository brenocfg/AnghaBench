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
struct omap_overlay {int (* enable ) (struct omap_overlay*) ;int (* disable ) (struct omap_overlay*) ;} ;

/* Variables and functions */
 int stub1 (struct omap_overlay*) ; 
 int stub2 (struct omap_overlay*) ; 

__attribute__((used)) static inline int omapfb_overlay_enable(struct omap_overlay *ovl,
		int enable)
{
	if (enable)
		return ovl->enable(ovl);
	else
		return ovl->disable(ovl);
}