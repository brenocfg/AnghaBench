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
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_guest_code_active () ; 
 int /*<<< orphan*/  vmci_host_active_users ; 
 scalar_t__ vmci_host_device_initialized ; 

bool vmci_host_code_active(void)
{
	return vmci_host_device_initialized &&
	    (!vmci_guest_code_active() ||
	     atomic_read(&vmci_host_active_users) > 0);
}