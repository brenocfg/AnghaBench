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
typedef  int ssize_t ;

/* Variables and functions */
 int strtobool (char const*,int*) ; 
 int stub1 (struct omap_overlay*) ; 
 int stub2 (struct omap_overlay*) ; 

__attribute__((used)) static ssize_t overlay_enabled_store(struct omap_overlay *ovl, const char *buf,
		size_t size)
{
	int r;
	bool enable;

	r = strtobool(buf, &enable);
	if (r)
		return r;

	if (enable)
		r = ovl->enable(ovl);
	else
		r = ovl->disable(ovl);

	if (r)
		return r;

	return size;
}