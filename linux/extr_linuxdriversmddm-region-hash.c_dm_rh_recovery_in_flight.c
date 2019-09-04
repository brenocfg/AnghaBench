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
struct dm_region_hash {int /*<<< orphan*/  recovery_in_flight; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

int dm_rh_recovery_in_flight(struct dm_region_hash *rh)
{
	return atomic_read(&rh->recovery_in_flight);
}