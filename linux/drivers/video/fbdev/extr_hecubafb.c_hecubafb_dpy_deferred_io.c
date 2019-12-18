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
struct list_head {int dummy; } ;
struct fb_info {int /*<<< orphan*/  par; } ;

/* Variables and functions */
 int /*<<< orphan*/  hecubafb_dpy_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hecubafb_dpy_deferred_io(struct fb_info *info,
				struct list_head *pagelist)
{
	hecubafb_dpy_update(info->par);
}