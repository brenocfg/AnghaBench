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
struct i810fb_par {int dev_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  accel_flags; } ;
struct fb_info {TYPE_1__ var; struct i810fb_par* par; } ;

/* Variables and functions */
 int LOCKUP ; 
 int wait_for_engine_idle (struct fb_info*) ; 

int i810fb_sync(struct fb_info *info)
{
	struct i810fb_par *par = info->par;
	
	if (!info->var.accel_flags || par->dev_flags & LOCKUP)
		return 0;

	return wait_for_engine_idle(info);
}