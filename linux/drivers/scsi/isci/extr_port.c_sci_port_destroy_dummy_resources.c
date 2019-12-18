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
struct isci_port {int /*<<< orphan*/  reserved_tag; int /*<<< orphan*/  reserved_rni; struct isci_host* owning_controller; } ;
struct isci_host {int /*<<< orphan*/  available_remote_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  SCU_DUMMY_INDEX ; 
 int /*<<< orphan*/  isci_free_tag (struct isci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_remote_node_table_release_remote_node_index (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_port_destroy_dummy_resources(struct isci_port *iport)
{
	struct isci_host *ihost = iport->owning_controller;

	if (iport->reserved_tag != SCI_CONTROLLER_INVALID_IO_TAG)
		isci_free_tag(ihost, iport->reserved_tag);

	if (iport->reserved_rni != SCU_DUMMY_INDEX)
		sci_remote_node_table_release_remote_node_index(&ihost->available_remote_nodes,
								     1, iport->reserved_rni);

	iport->reserved_rni = SCU_DUMMY_INDEX;
	iport->reserved_tag = SCI_CONTROLLER_INVALID_IO_TAG;
}