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
struct edac_pci_ctl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  edac_pci_remove_sysfs (struct edac_pci_ctl_info*) ; 

void edac_pci_free_ctl_info(struct edac_pci_ctl_info *pci)
{
	edac_dbg(1, "\n");

	edac_pci_remove_sysfs(pci);
}