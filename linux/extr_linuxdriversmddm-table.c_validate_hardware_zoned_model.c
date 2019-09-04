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
struct dm_table {int /*<<< orphan*/  md; } ;
typedef  enum blk_zoned_model { ____Placeholder_blk_zoned_model } blk_zoned_model ;

/* Variables and functions */
 int BLK_ZONED_NONE ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_matches_zone_sectors (struct dm_table*,unsigned int) ; 
 int /*<<< orphan*/  dm_table_supports_zoned_model (struct dm_table*,int) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 

__attribute__((used)) static int validate_hardware_zoned_model(struct dm_table *table,
					 enum blk_zoned_model zoned_model,
					 unsigned int zone_sectors)
{
	if (zoned_model == BLK_ZONED_NONE)
		return 0;

	if (!dm_table_supports_zoned_model(table, zoned_model)) {
		DMERR("%s: zoned model is not consistent across all devices",
		      dm_device_name(table->md));
		return -EINVAL;
	}

	/* Check zone size validity and compatibility */
	if (!zone_sectors || !is_power_of_2(zone_sectors))
		return -EINVAL;

	if (!dm_table_matches_zone_sectors(table, zone_sectors)) {
		DMERR("%s: zone sectors is not consistent across all devices",
		      dm_device_name(table->md));
		return -EINVAL;
	}

	return 0;
}