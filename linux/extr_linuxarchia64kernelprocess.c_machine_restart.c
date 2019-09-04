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
 int /*<<< orphan*/  DIE_MACHINE_RESTART ; 
 int /*<<< orphan*/  REBOOT_WARM ; 
 int /*<<< orphan*/  efi_reboot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_die (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
machine_restart (char *restart_cmd)
{
	(void) notify_die(DIE_MACHINE_RESTART, restart_cmd, NULL, 0, 0, 0);
	efi_reboot(REBOOT_WARM, NULL);
}