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
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  free_slots () ; 
 int /*<<< orphan*/  ibmphp_free_bus_info_queue () ; 
 int /*<<< orphan*/  ibmphp_free_ebda_hpc_queue () ; 
 int /*<<< orphan*/  ibmphp_free_ebda_pci_rsrc_queue () ; 
 int /*<<< orphan*/  ibmphp_free_resources () ; 
 int /*<<< orphan*/  ibmphp_pci_bus ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmphp_unload(void)
{
	free_slots();
	debug("after slots\n");
	ibmphp_free_resources();
	debug("after resources\n");
	ibmphp_free_bus_info_queue();
	debug("after bus info\n");
	ibmphp_free_ebda_hpc_queue();
	debug("after ebda hpc\n");
	ibmphp_free_ebda_pci_rsrc_queue();
	debug("after ebda pci rsrc\n");
	kfree(ibmphp_pci_bus);
}