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
typedef  int u32 ;
struct pci_host_bridge {struct pci_bus* bus; } ;
struct pci_bus {void* cur_bus_speed; void* max_bus_speed; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 void* PCIE_SPEED_2_5GT ; 
 void* PCIE_SPEED_5_0GT ; 
 void* PCIE_SPEED_8_0GT ; 
 void* PCI_SPEED_UNKNOWN ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int*,int) ; 
 scalar_t__ pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_set_host_bridge_release (struct pci_host_bridge*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pcibios_free_controller_deferred ; 
 struct device_node* pcibios_get_phb_of_node (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int pseries_root_bridge_prepare(struct pci_host_bridge *bridge)
{
	struct device_node *dn, *pdn;
	struct pci_bus *bus;
	u32 pcie_link_speed_stats[2];
	int rc;

	bus = bridge->bus;

	/* Rely on the pcibios_free_controller_deferred() callback. */
	pci_set_host_bridge_release(bridge, pcibios_free_controller_deferred,
					(void *) pci_bus_to_host(bus));

	dn = pcibios_get_phb_of_node(bus);
	if (!dn)
		return 0;

	for (pdn = dn; pdn != NULL; pdn = of_get_next_parent(pdn)) {
		rc = of_property_read_u32_array(pdn,
				"ibm,pcie-link-speed-stats",
				&pcie_link_speed_stats[0], 2);
		if (!rc)
			break;
	}

	of_node_put(pdn);

	if (rc) {
		pr_debug("no ibm,pcie-link-speed-stats property\n");
		return 0;
	}

	switch (pcie_link_speed_stats[0]) {
	case 0x01:
		bus->max_bus_speed = PCIE_SPEED_2_5GT;
		break;
	case 0x02:
		bus->max_bus_speed = PCIE_SPEED_5_0GT;
		break;
	case 0x04:
		bus->max_bus_speed = PCIE_SPEED_8_0GT;
		break;
	default:
		bus->max_bus_speed = PCI_SPEED_UNKNOWN;
		break;
	}

	switch (pcie_link_speed_stats[1]) {
	case 0x01:
		bus->cur_bus_speed = PCIE_SPEED_2_5GT;
		break;
	case 0x02:
		bus->cur_bus_speed = PCIE_SPEED_5_0GT;
		break;
	case 0x04:
		bus->cur_bus_speed = PCIE_SPEED_8_0GT;
		break;
	default:
		bus->cur_bus_speed = PCI_SPEED_UNKNOWN;
		break;
	}

	return 0;
}