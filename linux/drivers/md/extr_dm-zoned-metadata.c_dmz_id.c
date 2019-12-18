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
struct dmz_metadata {struct dm_zone* zones; } ;
struct dm_zone {int dummy; } ;

/* Variables and functions */

unsigned int dmz_id(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	return ((unsigned int)(zone - zmd->zones));
}