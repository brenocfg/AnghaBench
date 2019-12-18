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
struct dm_zone {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_RECLAIM ; 
 scalar_t__ dmz_is_active (struct dm_zone*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dmz_lock_zone_reclaim(struct dm_zone *zone)
{
	/* Active zones cannot be reclaimed */
	if (dmz_is_active(zone))
		return 0;

	return !test_and_set_bit(DMZ_RECLAIM, &zone->flags);
}