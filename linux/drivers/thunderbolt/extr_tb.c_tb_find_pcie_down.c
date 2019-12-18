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
struct TYPE_2__ {int max_port_number; } ;
struct tb_switch {struct tb_port* ports; TYPE_1__ config; } ;
struct tb_port {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_TYPE_PCIE_DOWN ; 
 scalar_t__ WARN_ON (int) ; 
 struct tb_port* tb_find_unused_port (struct tb_switch*,int /*<<< orphan*/ ) ; 
 int tb_pci_port_is_enabled (struct tb_port*) ; 
 int tb_phy_port_from_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_port_is_pcie_down (struct tb_port*) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 scalar_t__ tb_switch_is_cr (struct tb_switch*) ; 
 scalar_t__ tb_switch_is_fr (struct tb_switch*) ; 

__attribute__((used)) static struct tb_port *tb_find_pcie_down(struct tb_switch *sw,
					 const struct tb_port *port)
{
	/*
	 * To keep plugging devices consistently in the same PCIe
	 * hierarchy, do mapping here for root switch downstream PCIe
	 * ports.
	 */
	if (!tb_route(sw)) {
		int phy_port = tb_phy_port_from_link(port->port);
		int index;

		/*
		 * Hard-coded Thunderbolt port to PCIe down port mapping
		 * per controller.
		 */
		if (tb_switch_is_cr(sw))
			index = !phy_port ? 6 : 7;
		else if (tb_switch_is_fr(sw))
			index = !phy_port ? 6 : 8;
		else
			goto out;

		/* Validate the hard-coding */
		if (WARN_ON(index > sw->config.max_port_number))
			goto out;
		if (WARN_ON(!tb_port_is_pcie_down(&sw->ports[index])))
			goto out;
		if (WARN_ON(tb_pci_port_is_enabled(&sw->ports[index])))
			goto out;

		return &sw->ports[index];
	}

out:
	return tb_find_unused_port(sw, TB_TYPE_PCIE_DOWN);
}