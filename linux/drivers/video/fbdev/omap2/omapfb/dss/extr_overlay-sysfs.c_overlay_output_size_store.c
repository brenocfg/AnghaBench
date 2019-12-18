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
struct omap_overlay_info {void* out_height; void* out_width; } ;
struct omap_overlay {int (* set_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;TYPE_1__* manager; int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;} ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* apply ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 void* simple_strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub2 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int stub3 (TYPE_1__*) ; 

__attribute__((used)) static ssize_t overlay_output_size_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	char *last;
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	info.out_width = simple_strtoul(buf, &last, 10);
	++last;
	if (last - buf >= size)
		return -EINVAL;

	info.out_height = simple_strtoul(last, &last, 10);

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}