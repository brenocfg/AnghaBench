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
struct dmz_metadata {int /*<<< orphan*/  dev; } ;
struct dm_zone {unsigned int wp_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmz_dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_invalidate_blocks (struct dmz_metadata*,struct dm_zone*,unsigned int,unsigned int) ; 
 int dmz_update_zone (struct dmz_metadata*,struct dm_zone*) ; 

__attribute__((used)) static int dmz_handle_seq_write_err(struct dmz_metadata *zmd,
				    struct dm_zone *zone)
{
	unsigned int wp = 0;
	int ret;

	wp = zone->wp_block;
	ret = dmz_update_zone(zmd, zone);
	if (ret)
		return ret;

	dmz_dev_warn(zmd->dev, "Processing zone %u write error (zone wp %u/%u)",
		     dmz_id(zmd, zone), zone->wp_block, wp);

	if (zone->wp_block < wp) {
		dmz_invalidate_blocks(zmd, zone, zone->wp_block,
				      wp - zone->wp_block);
	}

	return 0;
}