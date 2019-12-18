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
struct dm_snapshot {TYPE_2__* store; } ;
struct TYPE_3__ {int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;
struct TYPE_4__ {int chunk_size; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 

__attribute__((used)) static bool io_overlaps_chunk(struct dm_snapshot *s, struct bio *bio)
{
	return bio->bi_iter.bi_size ==
		(s->store->chunk_size << SECTOR_SHIFT);
}