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
struct mmp_path {int overlay_num; TYPE_1__* overlays; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */

__attribute__((used)) static int path_check_status(struct mmp_path *path)
{
	int i;
	for (i = 0; i < path->overlay_num; i++)
		if (path->overlays[i].status)
			return 1;

	return 0;
}