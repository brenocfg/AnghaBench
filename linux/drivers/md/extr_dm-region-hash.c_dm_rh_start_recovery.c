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
struct dm_region_hash {int max_recovery; int /*<<< orphan*/  context; int /*<<< orphan*/  (* wakeup_workers ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  recovery_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void dm_rh_start_recovery(struct dm_region_hash *rh)
{
	int i;

	for (i = 0; i < rh->max_recovery; i++)
		up(&rh->recovery_count);

	rh->wakeup_workers(rh->context);
}