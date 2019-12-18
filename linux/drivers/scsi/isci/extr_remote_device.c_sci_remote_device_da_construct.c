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
struct sci_port_properties {int /*<<< orphan*/  phy_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_node_index; } ;
struct isci_remote_device {int /*<<< orphan*/  connection_rate; TYPE_1__ rnc; int /*<<< orphan*/  device_port_width; } ;
struct isci_port {int /*<<< orphan*/  owning_controller; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  hweight32 (int /*<<< orphan*/ ) ; 
 int sci_controller_allocate_remote_node_context (int /*<<< orphan*/ ,struct isci_remote_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_port_get_max_allowed_speed (struct isci_port*) ; 
 int /*<<< orphan*/  sci_port_get_properties (struct isci_port*,struct sci_port_properties*) ; 
 int /*<<< orphan*/  sci_remote_device_construct (struct isci_port*,struct isci_remote_device*) ; 

__attribute__((used)) static enum sci_status sci_remote_device_da_construct(struct isci_port *iport,
						       struct isci_remote_device *idev)
{
	enum sci_status status;
	struct sci_port_properties properties;

	sci_remote_device_construct(iport, idev);

	sci_port_get_properties(iport, &properties);
	/* Get accurate port width from port's phy mask for a DA device. */
	idev->device_port_width = hweight32(properties.phy_mask);

	status = sci_controller_allocate_remote_node_context(iport->owning_controller,
							     idev,
							     &idev->rnc.remote_node_index);

	if (status != SCI_SUCCESS)
		return status;

	idev->connection_rate = sci_port_get_max_allowed_speed(iport);

	return SCI_SUCCESS;
}