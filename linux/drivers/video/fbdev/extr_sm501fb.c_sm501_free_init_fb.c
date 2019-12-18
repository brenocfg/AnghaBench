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
struct sm501fb_info {struct fb_info** fb; } ;
struct fb_info {int /*<<< orphan*/  cmap; } ;
typedef  enum sm501_controller { ____Placeholder_sm501_controller } sm501_controller ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sm501_free_init_fb(struct sm501fb_info *info,
				enum sm501_controller head)
{
	struct fb_info *fbi = info->fb[head];

	if (!fbi)
		return;

	fb_dealloc_cmap(&fbi->cmap);
}