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
struct sci_sas_address {int dummy; } ;
struct sci_port_configuration_agent {TYPE_1__* phy_valid_port_range; } ;
struct isci_host {int /*<<< orphan*/ * phys; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
struct TYPE_2__ {int max_index; int min_index; } ;

/* Variables and functions */
 int SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_phy_get_sas_address (int /*<<< orphan*/ *,struct sci_sas_address*) ; 
 scalar_t__ sci_sas_address_compare (struct sci_sas_address,struct sci_sas_address) ; 

__attribute__((used)) static enum sci_status sci_port_configuration_agent_validate_ports(
	struct isci_host *ihost,
	struct sci_port_configuration_agent *port_agent)
{
	struct sci_sas_address first_address;
	struct sci_sas_address second_address;

	/*
	 * Sanity check the max ranges for all the phys the max index
	 * is always equal to the port range index */
	if (port_agent->phy_valid_port_range[0].max_index != 0 ||
	    port_agent->phy_valid_port_range[1].max_index != 1 ||
	    port_agent->phy_valid_port_range[2].max_index != 2 ||
	    port_agent->phy_valid_port_range[3].max_index != 3)
		return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;

	/*
	 * This is a request to configure a single x4 port or at least attempt
	 * to make all the phys into a single port */
	if (port_agent->phy_valid_port_range[0].min_index == 0 &&
	    port_agent->phy_valid_port_range[1].min_index == 0 &&
	    port_agent->phy_valid_port_range[2].min_index == 0 &&
	    port_agent->phy_valid_port_range[3].min_index == 0)
		return SCI_SUCCESS;

	/*
	 * This is a degenerate case where phy 1 and phy 2 are assigned
	 * to the same port this is explicitly disallowed by the hardware
	 * unless they are part of the same x4 port and this condition was
	 * already checked above. */
	if (port_agent->phy_valid_port_range[2].min_index == 1) {
		return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
	}

	/*
	 * PE0 and PE3 can never have the same SAS Address unless they
	 * are part of the same x4 wide port and we have already checked
	 * for this condition. */
	sci_phy_get_sas_address(&ihost->phys[0], &first_address);
	sci_phy_get_sas_address(&ihost->phys[3], &second_address);

	if (sci_sas_address_compare(first_address, second_address) == 0) {
		return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
	}

	/*
	 * PE0 and PE1 are configured into a 2x1 ports make sure that the
	 * SAS Address for PE0 and PE2 are different since they can not be
	 * part of the same port. */
	if (port_agent->phy_valid_port_range[0].min_index == 0 &&
	    port_agent->phy_valid_port_range[1].min_index == 1) {
		sci_phy_get_sas_address(&ihost->phys[0], &first_address);
		sci_phy_get_sas_address(&ihost->phys[2], &second_address);

		if (sci_sas_address_compare(first_address, second_address) == 0) {
			return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		}
	}

	/*
	 * PE2 and PE3 are configured into a 2x1 ports make sure that the
	 * SAS Address for PE1 and PE3 are different since they can not be
	 * part of the same port. */
	if (port_agent->phy_valid_port_range[2].min_index == 2 &&
	    port_agent->phy_valid_port_range[3].min_index == 3) {
		sci_phy_get_sas_address(&ihost->phys[1], &first_address);
		sci_phy_get_sas_address(&ihost->phys[3], &second_address);

		if (sci_sas_address_compare(first_address, second_address) == 0) {
			return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		}
	}

	return SCI_SUCCESS;
}