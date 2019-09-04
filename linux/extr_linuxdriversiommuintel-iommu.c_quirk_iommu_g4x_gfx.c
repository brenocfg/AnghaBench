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
 scalar_t__ dmar_map_gfx ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void quirk_iommu_g4x_gfx(struct pci_dev *dev)
{
	/* G4x/GM45 integrated gfx dmar support is totally busted. */
	pr_info("Disabling IOMMU for graphics on this chipset\n");
	dmar_map_gfx = 0;
}