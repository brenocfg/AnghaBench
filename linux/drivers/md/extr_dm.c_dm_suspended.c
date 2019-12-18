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
struct dm_target {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int dm_suspended_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_get_md (int /*<<< orphan*/ ) ; 

int dm_suspended(struct dm_target *ti)
{
	return dm_suspended_md(dm_table_get_md(ti->table));
}