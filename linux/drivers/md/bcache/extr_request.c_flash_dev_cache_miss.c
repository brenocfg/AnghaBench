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
struct search {int dummy; } ;
struct btree {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int MAP_CONTINUE ; 
 int MAP_DONE ; 
 int /*<<< orphan*/  bio_advance (struct bio*,unsigned int) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  zero_fill_bio (struct bio*) ; 

__attribute__((used)) static int flash_dev_cache_miss(struct btree *b, struct search *s,
				struct bio *bio, unsigned int sectors)
{
	unsigned int bytes = min(sectors, bio_sectors(bio)) << 9;

	swap(bio->bi_iter.bi_size, bytes);
	zero_fill_bio(bio);
	swap(bio->bi_iter.bi_size, bytes);

	bio_advance(bio, bytes);

	if (!bio->bi_iter.bi_size)
		return MAP_DONE;

	return MAP_CONTINUE;
}