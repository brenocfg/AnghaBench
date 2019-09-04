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
struct dmz_reclaim {struct dmz_metadata* metadata; } ;
struct dmz_metadata {int dummy; } ;
struct dm_zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmz_free_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_lock_flush (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_lock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_flush (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_zone_reclaim (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unmap_zone (struct dmz_metadata*,struct dm_zone*) ; 

__attribute__((used)) static void dmz_reclaim_empty(struct dmz_reclaim *zrc, struct dm_zone *dzone)
{
	struct dmz_metadata *zmd = zrc->metadata;

	dmz_lock_flush(zmd);
	dmz_lock_map(zmd);
	dmz_unmap_zone(zmd, dzone);
	dmz_unlock_zone_reclaim(dzone);
	dmz_free_zone(zmd, dzone);
	dmz_unlock_map(zmd);
	dmz_unlock_flush(zmd);
}