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
struct dm_zone {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_RECLAIM ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  dmz_lock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_lock_metadata (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_metadata (struct dmz_metadata*) ; 
 int /*<<< orphan*/  wait_on_bit_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmz_wait_for_reclaim(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	dmz_unlock_map(zmd);
	dmz_unlock_metadata(zmd);
	wait_on_bit_timeout(&zone->flags, DMZ_RECLAIM, TASK_UNINTERRUPTIBLE, HZ);
	dmz_lock_metadata(zmd);
	dmz_lock_map(zmd);
}