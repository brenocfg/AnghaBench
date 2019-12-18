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
struct omapfb_plane_info {int dummy; } ;
struct omapfb_plane_struct {struct omapfb_plane_info info; } ;
struct fb_info {struct omapfb_plane_struct* par; } ;

/* Variables and functions */

__attribute__((used)) static int omapfb_query_plane(struct fb_info *fbi, struct omapfb_plane_info *pi)
{
	struct omapfb_plane_struct *plane = fbi->par;

	*pi = plane->info;
	return 0;
}