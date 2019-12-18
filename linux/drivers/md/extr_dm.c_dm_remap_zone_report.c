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
struct dm_target {scalar_t__ len; scalar_t__ begin; } ;
struct blk_zone {scalar_t__ start; scalar_t__ type; scalar_t__ cond; scalar_t__ wp; scalar_t__ len; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ BLK_ZONE_COND_EMPTY ; 
 scalar_t__ BLK_ZONE_COND_FULL ; 
 scalar_t__ BLK_ZONE_TYPE_CONVENTIONAL ; 
 int /*<<< orphan*/  memset (struct blk_zone*,int /*<<< orphan*/ ,int) ; 

void dm_remap_zone_report(struct dm_target *ti, sector_t start,
			  struct blk_zone *zones, unsigned int *nr_zones)
{
#ifdef CONFIG_BLK_DEV_ZONED
	struct blk_zone *zone;
	unsigned int nrz = *nr_zones;
	int i;

	/*
	 * Remap the start sector and write pointer position of the zones in
	 * the array. Since we may have obtained from the target underlying
	 * device more zones that the target size, also adjust the number
	 * of zones.
	 */
	for (i = 0; i < nrz; i++) {
		zone = zones + i;
		if (zone->start >= start + ti->len) {
			memset(zone, 0, sizeof(struct blk_zone) * (nrz - i));
			break;
		}

		zone->start = zone->start + ti->begin - start;
		if (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
			continue;

		if (zone->cond == BLK_ZONE_COND_FULL)
			zone->wp = zone->start + zone->len;
		else if (zone->cond == BLK_ZONE_COND_EMPTY)
			zone->wp = zone->start;
		else
			zone->wp = zone->wp + ti->begin - start;
	}

	*nr_zones = i;
#else /* !CONFIG_BLK_DEV_ZONED */
	*nr_zones = 0;
#endif
}