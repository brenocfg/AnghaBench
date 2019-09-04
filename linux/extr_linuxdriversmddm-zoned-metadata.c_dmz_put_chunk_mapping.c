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
struct dmz_metadata {int dummy; } ;
struct dm_zone {struct dm_zone* bzone; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmz_deactivate_zone (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_free_zone (struct dmz_metadata*,struct dm_zone*) ; 
 scalar_t__ dmz_is_active (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_lock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_lru_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unlock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unmap_zone (struct dmz_metadata*,struct dm_zone*) ; 
 scalar_t__ dmz_weight (struct dm_zone*) ; 

void dmz_put_chunk_mapping(struct dmz_metadata *zmd, struct dm_zone *dzone)
{
	struct dm_zone *bzone;

	dmz_lock_map(zmd);

	bzone = dzone->bzone;
	if (bzone) {
		if (dmz_weight(bzone))
			dmz_lru_zone(zmd, bzone);
		else {
			/* Empty buffer zone: reclaim it */
			dmz_unmap_zone(zmd, bzone);
			dmz_free_zone(zmd, bzone);
			bzone = NULL;
		}
	}

	/* Deactivate the data zone */
	dmz_deactivate_zone(dzone);
	if (dmz_is_active(dzone) || bzone || dmz_weight(dzone))
		dmz_lru_zone(zmd, dzone);
	else {
		/* Unbuffered inactive empty data zone: reclaim it */
		dmz_unmap_zone(zmd, dzone);
		dmz_free_zone(zmd, dzone);
	}

	dmz_unlock_map(zmd);
}