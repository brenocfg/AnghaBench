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
 int /*<<< orphan*/  cmci_supported (int*) ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  machine_check_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_banks_owned ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void cmci_recheck(void)
{
	unsigned long flags;
	int banks;

	if (!mce_available(raw_cpu_ptr(&cpu_info)) || !cmci_supported(&banks))
		return;

	local_irq_save(flags);
	machine_check_poll(0, this_cpu_ptr(&mce_banks_owned));
	local_irq_restore(flags);
}