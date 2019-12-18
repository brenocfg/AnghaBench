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
struct intelfb_info {int /*<<< orphan*/  open; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 struct intelfb_info* GET_DINFO (struct fb_info*) ; 
 int /*<<< orphan*/  intelfbhw_disable_irq (struct intelfb_info*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int intelfb_release(struct fb_info *info, int user)
{
	struct intelfb_info *dinfo = GET_DINFO(info);

	if (user) {
		dinfo->open--;
		msleep(1);
		if (!dinfo->open)
			intelfbhw_disable_irq(dinfo);
	}

	return 0;
}