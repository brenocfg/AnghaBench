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

/* Variables and functions */
 scalar_t__ PIL_NMI ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  prom_cif_direct (unsigned long*) ; 
 int /*<<< orphan*/  prom_entry_lock ; 
 int /*<<< orphan*/  prom_world (int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

void p1275_cmd_direct(unsigned long *args)
{
	unsigned long flags;

	local_save_flags(flags);
	local_irq_restore((unsigned long)PIL_NMI);
	raw_spin_lock(&prom_entry_lock);

	prom_world(1);
	prom_cif_direct(args);
	prom_world(0);

	raw_spin_unlock(&prom_entry_lock);
	local_irq_restore(flags);
}