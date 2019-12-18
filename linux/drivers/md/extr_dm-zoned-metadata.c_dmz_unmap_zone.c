#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dmz_metadata {int dummy; } ;
struct dm_zone {unsigned int chunk; int /*<<< orphan*/  link; TYPE_1__* bzone; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bzone; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BUF ; 
 unsigned int DMZ_MAP_UNMAPPED ; 
 scalar_t__ WARN_ON (TYPE_1__*) ; 
 unsigned int dmz_id (struct dmz_metadata*,TYPE_1__*) ; 
 int /*<<< orphan*/  dmz_set_chunk_mapping (struct dmz_metadata*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dmz_unmap_zone(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	unsigned int chunk = zone->chunk;
	unsigned int dzone_id;

	if (chunk == DMZ_MAP_UNMAPPED) {
		/* Already unmapped */
		return;
	}

	if (test_and_clear_bit(DMZ_BUF, &zone->flags)) {
		/*
		 * Unmapping the chunk buffer zone: clear only
		 * the chunk buffer mapping
		 */
		dzone_id = dmz_id(zmd, zone->bzone);
		zone->bzone->bzone = NULL;
		zone->bzone = NULL;

	} else {
		/*
		 * Unmapping the chunk data zone: the zone must
		 * not be buffered.
		 */
		if (WARN_ON(zone->bzone)) {
			zone->bzone->bzone = NULL;
			zone->bzone = NULL;
		}
		dzone_id = DMZ_MAP_UNMAPPED;
	}

	dmz_set_chunk_mapping(zmd, chunk, dzone_id, DMZ_MAP_UNMAPPED);

	zone->chunk = DMZ_MAP_UNMAPPED;
	list_del_init(&zone->link);
}