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
struct per_bio_data {int /*<<< orphan*/ * cell; } ;
struct cache {int /*<<< orphan*/  prison; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ dm_cell_put_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_prison_cell (struct cache*,int /*<<< orphan*/ *) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 

__attribute__((used)) static void bio_drop_shared_lock(struct cache *cache, struct bio *bio)
{
	struct per_bio_data *pb = get_per_bio_data(bio);

	if (pb->cell && dm_cell_put_v2(cache->prison, pb->cell))
		free_prison_cell(cache, pb->cell);
	pb->cell = NULL;
}