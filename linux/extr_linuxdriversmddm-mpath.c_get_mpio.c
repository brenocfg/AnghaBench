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
union map_info {struct dm_mpath_io* ptr; } ;
struct dm_mpath_io {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct dm_mpath_io *get_mpio(union map_info *info)
{
	return info->ptr;
}