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
struct omap_overlay_info {int pre_mult_alpha; } ;
struct omap_overlay {int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*,struct omap_overlay_info*) ; 

__attribute__((used)) static ssize_t overlay_pre_mult_alpha_show(struct omap_overlay *ovl,
		char *buf)
{
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d\n",
			info.pre_mult_alpha);
}