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
struct cache {int sectors_per_block; } ;
struct TYPE_2__ {int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 

__attribute__((used)) static bool bio_writes_complete_block(struct cache *cache, struct bio *bio)
{
	return (bio_data_dir(bio) == WRITE) &&
		(bio->bi_iter.bi_size == (cache->sectors_per_block << SECTOR_SHIFT));
}