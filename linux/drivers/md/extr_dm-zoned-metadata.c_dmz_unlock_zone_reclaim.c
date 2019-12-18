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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_in_reclaim (struct dm_zone*) ; 
 int dmz_is_active (struct dm_zone*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dmz_unlock_zone_reclaim(struct dm_zone *zone)
{
	WARN_ON(dmz_is_active(zone));
	WARN_ON(!dmz_in_reclaim(zone));

	clear_bit_unlock(DMZ_RECLAIM, &zone->flags);
	smp_mb__after_atomic();
	wake_up_bit(&zone->flags, DMZ_RECLAIM);
}