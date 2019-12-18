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
struct intel_uncore_mmio_debug {int unclaimed_mmio_check; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
intel_uncore_mmio_debug_init_early(struct intel_uncore_mmio_debug *mmio_debug)
{
	spin_lock_init(&mmio_debug->lock);
	mmio_debug->unclaimed_mmio_check = 1;
}