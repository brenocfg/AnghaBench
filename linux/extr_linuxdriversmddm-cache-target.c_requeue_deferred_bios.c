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
struct bio_list {int dummy; } ;
struct cache {struct bio_list deferred_bios; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DM_REQUEUE ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 

__attribute__((used)) static void requeue_deferred_bios(struct cache *cache)
{
	struct bio *bio;
	struct bio_list bios;

	bio_list_init(&bios);
	bio_list_merge(&bios, &cache->deferred_bios);
	bio_list_init(&cache->deferred_bios);

	while ((bio = bio_list_pop(&bios))) {
		bio->bi_status = BLK_STS_DM_REQUEUE;
		bio_endio(bio);
	}
}