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
struct TYPE_4__ {int is_valid; } ;
union scu_remote_node_context {TYPE_2__ ssp; } ;
struct sci_remote_node_context {int /*<<< orphan*/  remote_node_index; } ;
struct isci_remote_device {TYPE_1__* owning_port; } ;
struct isci_host {int dummy; } ;
struct TYPE_3__ {struct isci_host* owning_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_CONTEXT_COMMAND_POST_RNC_INVALIDATE ; 
 struct isci_remote_device* rnc_to_dev (struct sci_remote_node_context*) ; 
 int /*<<< orphan*/  sci_remote_device_post_request (struct isci_remote_device*,int /*<<< orphan*/ ) ; 
 union scu_remote_node_context* sci_rnc_by_id (struct isci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_remote_node_context_invalidate_context_buffer(struct sci_remote_node_context *sci_rnc)
{
	union scu_remote_node_context *rnc_buffer;
	struct isci_remote_device *idev = rnc_to_dev(sci_rnc);
	struct isci_host *ihost = idev->owning_port->owning_controller;

	rnc_buffer = sci_rnc_by_id(ihost, sci_rnc->remote_node_index);

	rnc_buffer->ssp.is_valid = false;

	sci_remote_device_post_request(rnc_to_dev(sci_rnc),
				       SCU_CONTEXT_COMMAND_POST_RNC_INVALIDATE);
}