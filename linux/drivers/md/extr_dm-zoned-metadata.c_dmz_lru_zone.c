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
struct dmz_metadata {int dummy; } ;
struct dm_zone {struct dm_zone* bzone; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dmz_lru_zone (struct dmz_metadata*,struct dm_zone*) ; 

__attribute__((used)) static void dmz_lru_zone(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	__dmz_lru_zone(zmd, zone);
	if (zone->bzone)
		__dmz_lru_zone(zmd, zone->bzone);
}