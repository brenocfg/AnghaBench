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
struct TYPE_2__ {int /*<<< orphan*/  remote_node_index; } ;
struct isci_remote_device {int device_port_width; int /*<<< orphan*/  connection_rate; TYPE_1__ rnc; struct domain_device* domain_dev; } ;
struct isci_port {int /*<<< orphan*/  owning_controller; } ;
struct domain_device {int /*<<< orphan*/  linkrate; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sci_controller_allocate_remote_node_context (int /*<<< orphan*/ ,struct isci_remote_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_port_get_max_allowed_speed (struct isci_port*) ; 
 int /*<<< orphan*/  sci_remote_device_construct (struct isci_port*,struct isci_remote_device*) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static enum sci_status sci_remote_device_ea_construct(struct isci_port *iport,
						       struct isci_remote_device *idev)
{
	struct domain_device *dev = idev->domain_dev;
	enum sci_status status;

	sci_remote_device_construct(iport, idev);

	status = sci_controller_allocate_remote_node_context(iport->owning_controller,
								  idev,
								  &idev->rnc.remote_node_index);
	if (status != SCI_SUCCESS)
		return status;

	/* For SAS-2 the physical link rate is actually a logical link
	 * rate that incorporates multiplexing.  The SCU doesn't
	 * incorporate multiplexing and for the purposes of the
	 * connection the logical link rate is that same as the
	 * physical.  Furthermore, the SAS-2 and SAS-1.1 fields overlay
	 * one another, so this code works for both situations.
	 */
	idev->connection_rate = min_t(u16, sci_port_get_max_allowed_speed(iport),
					 dev->linkrate);

	/* / @todo Should I assign the port width by reading all of the phys on the port? */
	idev->device_port_width = 1;

	return SCI_SUCCESS;
}