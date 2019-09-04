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
 int /*<<< orphan*/  arch_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_proc_fin () ; 
 int /*<<< orphan*/  do_kernel_restart (char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  reboot_mode_nds32 ; 
 int /*<<< orphan*/  setup_mm_for_reboot (int /*<<< orphan*/ ) ; 

void machine_restart(char *cmd)
{
	/*
	 * Clean and disable cache, and turn off interrupts
	 */
	cpu_proc_fin();

	/*
	 * Tell the mm system that we are going to reboot -
	 * we may need it to insert some 1:1 mappings so that
	 * soft boot works.
	 */
	setup_mm_for_reboot(reboot_mode_nds32);

	/* Execute kernel restart handler call chain */
	do_kernel_restart(cmd);

	/*
	 * Now call the architecture specific reboot code.
	 */
	arch_reset(reboot_mode_nds32);

	/*
	 * Whoops - the architecture was unable to reboot.
	 * Tell the user!
	 */
	mdelay(1000);
	pr_info("Reboot failed -- System halted\n");
	while (1) ;
}