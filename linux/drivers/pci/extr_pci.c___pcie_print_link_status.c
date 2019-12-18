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
struct pci_dev {int dummy; } ;
typedef  enum pcie_link_width { ____Placeholder_pcie_link_width } pcie_link_width ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_SPEED2STR (int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int,int /*<<< orphan*/ ,int,...) ; 
 char* pci_name (struct pci_dev*) ; 
 int pcie_bandwidth_available (struct pci_dev*,struct pci_dev**,int*,int*) ; 
 int pcie_bandwidth_capable (struct pci_dev*,int*,int*) ; 

void __pcie_print_link_status(struct pci_dev *dev, bool verbose)
{
	enum pcie_link_width width, width_cap;
	enum pci_bus_speed speed, speed_cap;
	struct pci_dev *limiting_dev = NULL;
	u32 bw_avail, bw_cap;

	bw_cap = pcie_bandwidth_capable(dev, &speed_cap, &width_cap);
	bw_avail = pcie_bandwidth_available(dev, &limiting_dev, &speed, &width);

	if (bw_avail >= bw_cap && verbose)
		pci_info(dev, "%u.%03u Gb/s available PCIe bandwidth (%s x%d link)\n",
			 bw_cap / 1000, bw_cap % 1000,
			 PCIE_SPEED2STR(speed_cap), width_cap);
	else if (bw_avail < bw_cap)
		pci_info(dev, "%u.%03u Gb/s available PCIe bandwidth, limited by %s x%d link at %s (capable of %u.%03u Gb/s with %s x%d link)\n",
			 bw_avail / 1000, bw_avail % 1000,
			 PCIE_SPEED2STR(speed), width,
			 limiting_dev ? pci_name(limiting_dev) : "<unknown>",
			 bw_cap / 1000, bw_cap % 1000,
			 PCIE_SPEED2STR(speed_cap), width_cap);
}