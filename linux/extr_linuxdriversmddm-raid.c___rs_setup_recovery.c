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
struct TYPE_2__ {void* recovery_cp; } ;
struct raid_set {int /*<<< orphan*/  ctr_flags; TYPE_1__ md; } ;
typedef  void* sector_t ;

/* Variables and functions */
 void* MaxSector ; 
 int /*<<< orphan*/  __CTR_FLAG_NOSYNC ; 
 scalar_t__ rs_is_raid0 (struct raid_set*) ; 
 scalar_t__ rs_is_raid6 (struct raid_set*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rs_setup_recovery(struct raid_set *rs, sector_t dev_sectors)
{
	/* raid0 does not recover */
	if (rs_is_raid0(rs))
		rs->md.recovery_cp = MaxSector;
	/*
	 * A raid6 set has to be recovered either
	 * completely or for the grown part to
	 * ensure proper parity and Q-Syndrome
	 */
	else if (rs_is_raid6(rs))
		rs->md.recovery_cp = dev_sectors;
	/*
	 * Other raid set types may skip recovery
	 * depending on the 'nosync' flag.
	 */
	else
		rs->md.recovery_cp = test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags)
				     ? MaxSector : dev_sectors;
}