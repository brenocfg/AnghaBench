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
struct dmz_metadata {int /*<<< orphan*/  map_rnd_list; } ;
struct dm_zone {int /*<<< orphan*/  link; struct dm_zone* bzone; int /*<<< orphan*/  chunk; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_ALLOC_RND ; 
 int /*<<< orphan*/  DMZ_BUF ; 
 struct dm_zone* dmz_alloc_zone (struct dmz_metadata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_lock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_set_chunk_mapping (struct dmz_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_unlock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_wait_for_free_zones (struct dmz_metadata*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct dm_zone *dmz_get_chunk_buffer(struct dmz_metadata *zmd,
				     struct dm_zone *dzone)
{
	struct dm_zone *bzone;

	dmz_lock_map(zmd);
again:
	bzone = dzone->bzone;
	if (bzone)
		goto out;

	/* Alloate a random zone */
	bzone = dmz_alloc_zone(zmd, DMZ_ALLOC_RND);
	if (!bzone) {
		dmz_wait_for_free_zones(zmd);
		goto again;
	}

	/* Update the chunk mapping */
	dmz_set_chunk_mapping(zmd, dzone->chunk, dmz_id(zmd, dzone),
			      dmz_id(zmd, bzone));

	set_bit(DMZ_BUF, &bzone->flags);
	bzone->chunk = dzone->chunk;
	bzone->bzone = dzone;
	dzone->bzone = bzone;
	list_add_tail(&bzone->link, &zmd->map_rnd_list);
out:
	dmz_unlock_map(zmd);

	return bzone;
}