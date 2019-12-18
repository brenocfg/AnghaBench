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
struct radeonfb_info {int dummy; } ;
struct fb_info {scalar_t__ state; struct radeonfb_info* par; } ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  radeon_engine_idle () ; 

int radeonfb_sync(struct fb_info *info)
{
	struct radeonfb_info *rinfo = info->par;

	if (info->state != FBINFO_STATE_RUNNING)
		return 0;
	radeon_engine_idle();

	return 0;
}