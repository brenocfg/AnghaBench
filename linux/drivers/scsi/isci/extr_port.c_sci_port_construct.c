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
struct isci_port {size_t physical_port_index; int ready_exit; int /*<<< orphan*/ ** phy_table; int /*<<< orphan*/ * port_task_scheduler_registers; int /*<<< orphan*/  timer; int /*<<< orphan*/  reserved_tag; int /*<<< orphan*/  reserved_rni; scalar_t__ hang_detect_users; scalar_t__ assigned_device_count; scalar_t__ started_request_count; struct isci_host* owning_controller; scalar_t__ last_active_phy; scalar_t__ enabled_phy_mask; scalar_t__ active_phy_mask; int /*<<< orphan*/  logical_port_index; int /*<<< orphan*/  sm; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_DUMMY_PORT ; 
 int /*<<< orphan*/  SCI_CONTROLLER_INVALID_IO_TAG ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  SCI_PORT_STOPPED ; 
 int /*<<< orphan*/  SCU_DUMMY_INDEX ; 
 int /*<<< orphan*/  port_timeout ; 
 int /*<<< orphan*/  sci_init_sm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_port_state_table ; 

void sci_port_construct(struct isci_port *iport, u8 index,
			     struct isci_host *ihost)
{
	sci_init_sm(&iport->sm, sci_port_state_table, SCI_PORT_STOPPED);

	iport->logical_port_index  = SCIC_SDS_DUMMY_PORT;
	iport->physical_port_index = index;
	iport->active_phy_mask     = 0;
	iport->enabled_phy_mask    = 0;
	iport->last_active_phy     = 0;
	iport->ready_exit	   = false;

	iport->owning_controller = ihost;

	iport->started_request_count = 0;
	iport->assigned_device_count = 0;
	iport->hang_detect_users = 0;

	iport->reserved_rni = SCU_DUMMY_INDEX;
	iport->reserved_tag = SCI_CONTROLLER_INVALID_IO_TAG;

	sci_init_timer(&iport->timer, port_timeout);

	iport->port_task_scheduler_registers = NULL;

	for (index = 0; index < SCI_MAX_PHYS; index++)
		iport->phy_table[index] = NULL;
}