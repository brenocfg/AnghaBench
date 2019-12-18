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
typedef  int /*<<< orphan*/  u16 ;
struct scu_task_context {int initiator_request; int connection_rate; size_t task_index; int do_not_dma_ssp_good_response; int task_phase; int /*<<< orphan*/  remote_node_index; int /*<<< orphan*/  context_type; int /*<<< orphan*/  valid; int /*<<< orphan*/  protocol_type; int /*<<< orphan*/  logical_port_index; } ;
struct isci_port {int /*<<< orphan*/  reserved_rni; int /*<<< orphan*/  physical_port_index; struct isci_host* owning_controller; } ;
struct isci_host {struct scu_task_context* task_context_table; } ;

/* Variables and functions */
 size_t ISCI_TAG_TCI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_TASK_CONTEXT_PROTOCOL_SSP ; 
 int /*<<< orphan*/  SCU_TASK_CONTEXT_TYPE ; 
 int /*<<< orphan*/  SCU_TASK_CONTEXT_VALID ; 
 int /*<<< orphan*/  memset (struct scu_task_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sci_port_construct_dummy_task(struct isci_port *iport, u16 tag)
{
	struct isci_host *ihost = iport->owning_controller;
	struct scu_task_context *task_context;

	task_context = &ihost->task_context_table[ISCI_TAG_TCI(tag)];
	memset(task_context, 0, sizeof(struct scu_task_context));

	task_context->initiator_request = 1;
	task_context->connection_rate = 1;
	task_context->logical_port_index = iport->physical_port_index;
	task_context->protocol_type = SCU_TASK_CONTEXT_PROTOCOL_SSP;
	task_context->task_index = ISCI_TAG_TCI(tag);
	task_context->valid = SCU_TASK_CONTEXT_VALID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;
	task_context->remote_node_index = iport->reserved_rni;
	task_context->do_not_dma_ssp_good_response = 1;
	task_context->task_phase = 0x01;
}