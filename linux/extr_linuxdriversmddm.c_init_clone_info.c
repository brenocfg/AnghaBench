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
struct mapped_device {int dummy; } ;
struct dm_table {int dummy; } ;
struct clone_info {int /*<<< orphan*/  sector; int /*<<< orphan*/  io; struct dm_table* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_io (struct mapped_device*,struct bio*) ; 

__attribute__((used)) static void init_clone_info(struct clone_info *ci, struct mapped_device *md,
			    struct dm_table *map, struct bio *bio)
{
	ci->map = map;
	ci->io = alloc_io(md, bio);
	ci->sector = bio->bi_iter.bi_sector;
}