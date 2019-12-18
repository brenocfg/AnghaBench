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
struct MessageUnit_B {void* message_rwbuffer; void* message_rbuffer; void* message_wbuffer; void* iop2drv_doorbell_mask; void* iop2drv_doorbell; void* drv2iop_doorbell_mask; void* drv2iop_doorbell; } ;
struct AdapterControlBlock {TYPE_1__* pdev; struct MessageUnit_B* pmuB; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL_1203 ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL_MASK ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL_MASK_1203 ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL_1203 ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL_MASK ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL_MASK_1203 ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_RBUFFER ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_RWBUFFER ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_WBUFFER ; 
 void* MEM_BASE0 (int /*<<< orphan*/ ) ; 
 void* MEM_BASE1 (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_DEVICE_ID_ARECA_1203 ; 

__attribute__((used)) static void arcmsr_hbaB_assign_regAddr(struct AdapterControlBlock *acb)
{
	struct MessageUnit_B *reg = acb->pmuB;

	if (acb->pdev->device == PCI_DEVICE_ID_ARECA_1203) {
		reg->drv2iop_doorbell = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_1203);
		reg->drv2iop_doorbell_mask = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_MASK_1203);
		reg->iop2drv_doorbell = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_1203);
		reg->iop2drv_doorbell_mask = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_MASK_1203);
	} else {
		reg->drv2iop_doorbell= MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL);
		reg->drv2iop_doorbell_mask = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_MASK);
		reg->iop2drv_doorbell = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL);
		reg->iop2drv_doorbell_mask = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_MASK);
	}
	reg->message_wbuffer = MEM_BASE1(ARCMSR_MESSAGE_WBUFFER);
	reg->message_rbuffer =  MEM_BASE1(ARCMSR_MESSAGE_RBUFFER);
	reg->message_rwbuffer = MEM_BASE1(ARCMSR_MESSAGE_RWBUFFER);
}