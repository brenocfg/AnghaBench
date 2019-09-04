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
struct dm_zone {int /*<<< orphan*/  flags; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dmz_deactivate_zone(struct dm_zone *zone)
{
	if (atomic_dec_and_test(&zone->refcount)) {
		WARN_ON(!test_bit(DMZ_ACTIVE, &zone->flags));
		clear_bit_unlock(DMZ_ACTIVE, &zone->flags);
		smp_mb__after_atomic();
	}
}