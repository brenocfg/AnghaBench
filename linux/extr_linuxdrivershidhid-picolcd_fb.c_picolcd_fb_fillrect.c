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
struct fb_info {int /*<<< orphan*/  deferred_work; int /*<<< orphan*/  par; } ;
struct fb_fillrect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void picolcd_fb_fillrect(struct fb_info *info,
		const struct fb_fillrect *rect)
{
	if (!info->par)
		return;
	sys_fillrect(info, rect);

	schedule_delayed_work(&info->deferred_work, 0);
}