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
struct dmz_metadata {TYPE_1__* dev; } ;
struct dm_zone {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ zone_nr_blocks; } ;

/* Variables and functions */
 int dmz_to_next_set_block (struct dmz_metadata*,struct dm_zone*,scalar_t__,scalar_t__,int) ; 

int dmz_first_valid_block(struct dmz_metadata *zmd, struct dm_zone *zone,
			  sector_t *chunk_block)
{
	sector_t start_block = *chunk_block;
	int ret;

	ret = dmz_to_next_set_block(zmd, zone, start_block,
				    zmd->dev->zone_nr_blocks - start_block, 1);
	if (ret < 0)
		return ret;

	start_block += ret;
	*chunk_block = start_block;

	return dmz_to_next_set_block(zmd, zone, start_block,
				     zmd->dev->zone_nr_blocks - start_block, 0);
}