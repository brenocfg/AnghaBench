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
struct MessageUnit_D {void* msgcode_rwbuffer; void* message_rbuffer; void* message_wbuffer; void* outboundlist_interrupt_enable; void* outboundlist_interrupt_cause; void* outboundlist_read_pointer; void* outboundlist_copy_pointer; void* outboundlist_base_high; void* outboundlist_base_low; void* inboundlist_write_pointer; void* inboundlist_base_high; void* inboundlist_base_low; void* outbound_doorbell_enable; void* outbound_doorbell; void* inbound_doorbell; void* outbound_msgaddr1; void* outbound_msgaddr0; void* inbound_msgaddr1; void* inbound_msgaddr0; void* pcief0_int_enable; void* host_int_status; void* reset_request; void* sample_at_reset; void* i2o_host_interrupt_mask; void* cpu_mem_config; void* chip_id; } ;
struct AdapterControlBlock {struct MessageUnit_D* pmuD; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_ARC1214_CHIP_ID ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_CPU_MEMORY_CONFIGURATION ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_I2_HOST_INTERRUPT_MASK ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_LIST_BASE_HIGH ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_LIST_BASE_LOW ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_LIST_WRITE_POINTER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_MESSAGE0 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_MESSAGE1 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MAIN_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MESSAGE_RBUFFER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MESSAGE_RWBUFFER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MESSAGE_WBUFFER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_DOORBELL_ENABLE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_INTERRUPT_CAUSE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_BASE_HIGH ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_BASE_LOW ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_COPY_POINTER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_READ_POINTER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_MESSAGE0 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_MESSAGE1 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_PCIE_F0_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_RESET_REQUEST ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_SAMPLE_RESET ; 
 void* MEM_BASE0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_hbaD_assign_regAddr(struct AdapterControlBlock *acb)
{
	struct MessageUnit_D *reg = acb->pmuD;

	reg->chip_id = MEM_BASE0(ARCMSR_ARC1214_CHIP_ID);
	reg->cpu_mem_config = MEM_BASE0(ARCMSR_ARC1214_CPU_MEMORY_CONFIGURATION);
	reg->i2o_host_interrupt_mask = MEM_BASE0(ARCMSR_ARC1214_I2_HOST_INTERRUPT_MASK);
	reg->sample_at_reset = MEM_BASE0(ARCMSR_ARC1214_SAMPLE_RESET);
	reg->reset_request = MEM_BASE0(ARCMSR_ARC1214_RESET_REQUEST);
	reg->host_int_status = MEM_BASE0(ARCMSR_ARC1214_MAIN_INTERRUPT_STATUS);
	reg->pcief0_int_enable = MEM_BASE0(ARCMSR_ARC1214_PCIE_F0_INTERRUPT_ENABLE);
	reg->inbound_msgaddr0 = MEM_BASE0(ARCMSR_ARC1214_INBOUND_MESSAGE0);
	reg->inbound_msgaddr1 = MEM_BASE0(ARCMSR_ARC1214_INBOUND_MESSAGE1);
	reg->outbound_msgaddr0 = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_MESSAGE0);
	reg->outbound_msgaddr1 = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_MESSAGE1);
	reg->inbound_doorbell = MEM_BASE0(ARCMSR_ARC1214_INBOUND_DOORBELL);
	reg->outbound_doorbell = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_DOORBELL);
	reg->outbound_doorbell_enable = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_DOORBELL_ENABLE);
	reg->inboundlist_base_low = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_BASE_LOW);
	reg->inboundlist_base_high = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_BASE_HIGH);
	reg->inboundlist_write_pointer = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_WRITE_POINTER);
	reg->outboundlist_base_low = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_BASE_LOW);
	reg->outboundlist_base_high = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_BASE_HIGH);
	reg->outboundlist_copy_pointer = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_COPY_POINTER);
	reg->outboundlist_read_pointer = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_READ_POINTER);
	reg->outboundlist_interrupt_cause = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_INTERRUPT_CAUSE);
	reg->outboundlist_interrupt_enable = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_INTERRUPT_ENABLE);
	reg->message_wbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_WBUFFER);
	reg->message_rbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_RBUFFER);
	reg->msgcode_rwbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_RWBUFFER);
}