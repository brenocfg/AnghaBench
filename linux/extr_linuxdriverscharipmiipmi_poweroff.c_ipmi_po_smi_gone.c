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
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int ipmi_ifnum ; 
 int /*<<< orphan*/  ipmi_user ; 
 int /*<<< orphan*/  old_poweroff_func ; 
 int /*<<< orphan*/  pm_power_off ; 
 scalar_t__ ready ; 

__attribute__((used)) static void ipmi_po_smi_gone(int if_num)
{
	if (!ready)
		return;

	if (ipmi_ifnum != if_num)
		return;

	ready = 0;
	ipmi_destroy_user(ipmi_user);
	pm_power_off = old_poweroff_func;
}