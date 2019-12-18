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
struct per_bio_data {int /*<<< orphan*/  hook_info; } ;
struct TYPE_2__ {scalar_t__ input; } ;
struct dm_cache_migration {TYPE_1__ k; struct cache* cache; } ;
struct cache {int /*<<< orphan*/  wq; } ;
struct bio {scalar_t__ bi_status; struct dm_cache_migration* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_unhook_bio (int /*<<< orphan*/ *,struct bio*) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  queue_continuation (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void overwrite_endio(struct bio *bio)
{
	struct dm_cache_migration *mg = bio->bi_private;
	struct cache *cache = mg->cache;
	struct per_bio_data *pb = get_per_bio_data(bio);

	dm_unhook_bio(&pb->hook_info, bio);

	if (bio->bi_status)
		mg->k.input = bio->bi_status;

	queue_continuation(cache->wq, &mg->k);
}