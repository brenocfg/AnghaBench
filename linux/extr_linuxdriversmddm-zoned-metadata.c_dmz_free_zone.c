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
struct dmz_metadata {scalar_t__ nr_reserved_seq; int /*<<< orphan*/  free_wq; int /*<<< orphan*/  unmap_nr_seq; int /*<<< orphan*/  unmap_seq_list; int /*<<< orphan*/  nr_reserved_seq_zones; int /*<<< orphan*/  reserved_seq_zones_list; int /*<<< orphan*/  unmap_nr_rnd; int /*<<< orphan*/  unmap_rnd_list; } ;
struct dm_zone {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ dmz_is_rnd (struct dm_zone*) ; 
 scalar_t__ dmz_is_seq (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_reset_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void dmz_free_zone(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	/* If this is a sequential zone, reset it */
	if (dmz_is_seq(zone))
		dmz_reset_zone(zmd, zone);

	/* Return the zone to its type unmap list */
	if (dmz_is_rnd(zone)) {
		list_add_tail(&zone->link, &zmd->unmap_rnd_list);
		atomic_inc(&zmd->unmap_nr_rnd);
	} else if (atomic_read(&zmd->nr_reserved_seq_zones) <
		   zmd->nr_reserved_seq) {
		list_add_tail(&zone->link, &zmd->reserved_seq_zones_list);
		atomic_inc(&zmd->nr_reserved_seq_zones);
	} else {
		list_add_tail(&zone->link, &zmd->unmap_seq_list);
		atomic_inc(&zmd->unmap_nr_seq);
	}

	wake_up_all(&zmd->free_wq);
}