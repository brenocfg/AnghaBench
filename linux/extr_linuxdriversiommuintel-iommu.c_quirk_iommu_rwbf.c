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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int rwbf_quirk ; 

__attribute__((used)) static void quirk_iommu_rwbf(struct pci_dev *dev)
{
	/*
	 * Mobile 4 Series Chipset neglects to set RWBF capability,
	 * but needs it. Same seems to hold for the desktop versions.
	 */
	pr_info("Forcing write-buffer flush capability\n");
	rwbf_quirk = 1;
}