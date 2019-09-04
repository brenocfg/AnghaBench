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
typedef  int sector_t ;
struct TYPE_2__ {int zone_nr_sectors_shift; } ;

/* Variables and functions */
 scalar_t__ dmz_id (struct dmz_metadata*,struct dm_zone*) ; 

sector_t dmz_start_sect(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	return (sector_t)dmz_id(zmd, zone) << zmd->dev->zone_nr_sectors_shift;
}