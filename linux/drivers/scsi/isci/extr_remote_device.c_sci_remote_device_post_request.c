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
typedef  int u32 ;
struct TYPE_2__ {int remote_node_index; } ;
struct isci_remote_device {TYPE_1__ rnc; struct isci_port* owning_port; } ;
struct isci_port {int physical_port_index; int /*<<< orphan*/  owning_controller; } ;

/* Variables and functions */
 int ISCI_PEG ; 
 int SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT ; 
 int SCU_CONTEXT_COMMAND_PROTOCOL_ENGINE_GROUP_SHIFT ; 
 int /*<<< orphan*/  sci_controller_post_request (int /*<<< orphan*/ ,int) ; 

void sci_remote_device_post_request(struct isci_remote_device *idev, u32 request)
{
	struct isci_port *iport = idev->owning_port;
	u32 context;

	context = request |
		  (ISCI_PEG << SCU_CONTEXT_COMMAND_PROTOCOL_ENGINE_GROUP_SHIFT) |
		  (iport->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT) |
		  idev->rnc.remote_node_index;

	sci_controller_post_request(iport->owning_controller, context);
}