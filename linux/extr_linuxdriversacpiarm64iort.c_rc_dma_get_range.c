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
typedef  unsigned long long u64 ;
struct pci_bus {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct acpi_iort_root_complex {int memory_address_limit; } ;
struct acpi_iort_node {int revision; scalar_t__ node_data; } ;
struct TYPE_2__ {struct pci_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IORT_NODE_PCI_ROOT_COMPLEX ; 
 int ENODEV ; 
 unsigned long long U64_MAX ; 
 int /*<<< orphan*/  iort_match_node_callback ; 
 struct acpi_iort_node* iort_scan_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

__attribute__((used)) static int rc_dma_get_range(struct device *dev, u64 *size)
{
	struct acpi_iort_node *node;
	struct acpi_iort_root_complex *rc;
	struct pci_bus *pbus = to_pci_dev(dev)->bus;

	node = iort_scan_node(ACPI_IORT_NODE_PCI_ROOT_COMPLEX,
			      iort_match_node_callback, &pbus->dev);
	if (!node || node->revision < 1)
		return -ENODEV;

	rc = (struct acpi_iort_root_complex *)node->node_data;

	*size = rc->memory_address_limit >= 64 ? U64_MAX :
			1ULL<<rc->memory_address_limit;

	return 0;
}