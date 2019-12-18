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
struct intelfb_info {scalar_t__ ring_lockup; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 struct intelfb_info* GET_DINFO (struct fb_info*) ; 
 int /*<<< orphan*/  intelfbhw_do_sync (struct intelfb_info*) ; 

__attribute__((used)) static int intelfb_sync(struct fb_info *info)
{
        struct intelfb_info *dinfo = GET_DINFO(info);

#if VERBOSE > 0
	DBG_MSG("intelfb_sync\n");
#endif

	if (dinfo->ring_lockup)
		return 0;

	intelfbhw_do_sync(dinfo);
	return 0;
}