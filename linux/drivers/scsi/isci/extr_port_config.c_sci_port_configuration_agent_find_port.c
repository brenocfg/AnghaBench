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
typedef  size_t u8 ;
struct sci_sas_address {int dummy; } ;
struct isci_port {int dummy; } ;
struct isci_phy {int dummy; } ;
struct isci_host {size_t logical_port_entries; struct isci_port* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  sci_phy_get_attached_sas_address (struct isci_phy*,struct sci_sas_address*) ; 
 int /*<<< orphan*/  sci_phy_get_sas_address (struct isci_phy*,struct sci_sas_address*) ; 
 int /*<<< orphan*/  sci_port_get_attached_sas_address (struct isci_port*,struct sci_sas_address*) ; 
 int /*<<< orphan*/  sci_port_get_sas_address (struct isci_port*,struct sci_sas_address*) ; 
 scalar_t__ sci_sas_address_compare (struct sci_sas_address,struct sci_sas_address) ; 

__attribute__((used)) static struct isci_port *sci_port_configuration_agent_find_port(
	struct isci_host *ihost,
	struct isci_phy *iphy)
{
	u8 i;
	struct sci_sas_address port_sas_address;
	struct sci_sas_address port_attached_device_address;
	struct sci_sas_address phy_sas_address;
	struct sci_sas_address phy_attached_device_address;

	/*
	 * Since this phy can be a member of a wide port check to see if one or
	 * more phys match the sent and received SAS address as this phy in which
	 * case it should participate in the same port.
	 */
	sci_phy_get_sas_address(iphy, &phy_sas_address);
	sci_phy_get_attached_sas_address(iphy, &phy_attached_device_address);

	for (i = 0; i < ihost->logical_port_entries; i++) {
		struct isci_port *iport = &ihost->ports[i];

		sci_port_get_sas_address(iport, &port_sas_address);
		sci_port_get_attached_sas_address(iport, &port_attached_device_address);

		if (sci_sas_address_compare(port_sas_address, phy_sas_address) == 0 &&
		    sci_sas_address_compare(port_attached_device_address, phy_attached_device_address) == 0)
			return iport;
	}

	return NULL;
}