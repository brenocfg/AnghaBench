#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_NB_GART ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_gatt_table ; 
 int /*<<< orphan*/  amd_flush_garts () ; 
 int /*<<< orphan*/  amd_nb_has_feature (int /*<<< orphan*/ ) ; 
 int amd_nb_num () ; 
 int /*<<< orphan*/  enable_gart_translation (struct pci_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__* node_to_amd_nb (int) ; 

__attribute__((used)) static void enable_gart_translations(void)
{
	int i;

	if (!amd_nb_has_feature(AMD_NB_GART))
		return;

	for (i = 0; i < amd_nb_num(); i++) {
		struct pci_dev *dev = node_to_amd_nb(i)->misc;

		enable_gart_translation(dev, __pa(agp_gatt_table));
	}

	/* Flush the GART-TLB to remove stale entries */
	amd_flush_garts();
}