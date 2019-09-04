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
struct mapped_device {int dummy; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int flags; } ;

/* Variables and functions */
 int DM_QUERY_INACTIVE_TABLE_FLAG ; 
 struct dm_table* dm_get_inactive_table (struct mapped_device*,int*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 

__attribute__((used)) static struct dm_table *dm_get_live_or_inactive_table(struct mapped_device *md,
						      struct dm_ioctl *param,
						      int *srcu_idx)
{
	return (param->flags & DM_QUERY_INACTIVE_TABLE_FLAG) ?
		dm_get_inactive_table(md, srcu_idx) : dm_get_live_table(md, srcu_idx);
}