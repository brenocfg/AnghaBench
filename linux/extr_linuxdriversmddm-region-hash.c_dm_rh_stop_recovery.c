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
struct dm_region_hash {int max_recovery; int /*<<< orphan*/  recovery_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 

void dm_rh_stop_recovery(struct dm_region_hash *rh)
{
	int i;

	/* wait for any recovering regions */
	for (i = 0; i < rh->max_recovery; i++)
		down(&rh->recovery_count);
}