#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  array_sectors; } ;
struct raid_set {TYPE_2__ md; TYPE_1__* ti; } ;
struct gendisk {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 struct gendisk* dm_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_get_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_disk (struct gendisk*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_set_capacity(struct raid_set *rs)
{
	struct gendisk *gendisk = dm_disk(dm_table_get_md(rs->ti->table));

	set_capacity(gendisk, rs->md.array_sectors);
	revalidate_disk(gendisk);
}