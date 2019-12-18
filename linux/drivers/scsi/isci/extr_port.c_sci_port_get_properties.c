#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sas_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocols; int /*<<< orphan*/  sas_address; } ;
struct sci_port_properties {scalar_t__ index; TYPE_1__ remote; TYPE_2__ local; int /*<<< orphan*/  phy_mask; } ;
struct isci_port {scalar_t__ logical_port_index; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_DUMMY_PORT ; 
 int SCI_FAILURE_INVALID_PORT ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_port_get_attached_sas_address (struct isci_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_port_get_phys (struct isci_port*) ; 
 int /*<<< orphan*/  sci_port_get_protocols (struct isci_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_port_get_sas_address (struct isci_port*,int /*<<< orphan*/ *) ; 

enum sci_status sci_port_get_properties(struct isci_port *iport,
						struct sci_port_properties *prop)
{
	if (!iport || iport->logical_port_index == SCIC_SDS_DUMMY_PORT)
		return SCI_FAILURE_INVALID_PORT;

	prop->index = iport->logical_port_index;
	prop->phy_mask = sci_port_get_phys(iport);
	sci_port_get_sas_address(iport, &prop->local.sas_address);
	sci_port_get_protocols(iport, &prop->local.protocols);
	sci_port_get_attached_sas_address(iport, &prop->remote.sas_address);

	return SCI_SUCCESS;
}