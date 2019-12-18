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
struct radeon_sync {int /*<<< orphan*/ * last_vm_update; int /*<<< orphan*/ ** sync_to; int /*<<< orphan*/ ** semaphores; } ;

/* Variables and functions */
 unsigned int RADEON_NUM_RINGS ; 
 unsigned int RADEON_NUM_SYNCS ; 

void radeon_sync_create(struct radeon_sync *sync)
{
	unsigned i;

	for (i = 0; i < RADEON_NUM_SYNCS; ++i)
		sync->semaphores[i] = NULL;

	for (i = 0; i < RADEON_NUM_RINGS; ++i)
		sync->sync_to[i] = NULL;

	sync->last_vm_update = NULL;
}