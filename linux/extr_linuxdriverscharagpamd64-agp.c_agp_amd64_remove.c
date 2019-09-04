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
struct agp_bridge_data {size_t aperture_size_idx; int /*<<< orphan*/  gatt_table_real; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_bridges_found ; 
 int /*<<< orphan*/  agp_put_bridge (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  agp_remove_bridge (struct agp_bridge_data*) ; 
 TYPE_1__* amd64_aperture_sizes ; 
 struct agp_bridge_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void agp_amd64_remove(struct pci_dev *pdev)
{
	struct agp_bridge_data *bridge = pci_get_drvdata(pdev);

	release_mem_region(virt_to_phys(bridge->gatt_table_real),
			   amd64_aperture_sizes[bridge->aperture_size_idx].size);
	agp_remove_bridge(bridge);
	agp_put_bridge(bridge);

	agp_bridges_found--;
}