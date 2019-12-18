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
typedef  int uint32_t ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct deliver_completeQ {int dummy; } ;
struct MessageUnit_D {int dummy; } ;
struct MessageUnit_B {int dummy; } ;
struct AdapterControlBlock {int adapter_type; int ioqueue_size; int completionQ_entry; int /*<<< orphan*/  doneq_index; void* pCompletionQ; void* dma_coherent2; void* dma_coherent_handle2; TYPE_1__* host; struct MessageUnit_D* pmuD; struct MessageUnit_B* pmuB; struct pci_dev* pdev; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_B 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int ARCMSR_MAX_HBE_DONEQUEUE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  arcmsr_hbaB_assign_regAddr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaD_assign_regAddr (struct AdapterControlBlock*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 void* roundup (int,int) ; 

__attribute__((used)) static bool arcmsr_alloc_io_queue(struct AdapterControlBlock *acb)
{
	bool rtn = true;
	void *dma_coherent;
	dma_addr_t dma_coherent_handle;
	struct pci_dev *pdev = acb->pdev;

	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_B: {
		acb->ioqueue_size = roundup(sizeof(struct MessageUnit_B), 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		if (!dma_coherent) {
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			return false;
		}
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pmuB = (struct MessageUnit_B *)dma_coherent;
		arcmsr_hbaB_assign_regAddr(acb);
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
		acb->ioqueue_size = roundup(sizeof(struct MessageUnit_D), 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		if (!dma_coherent) {
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			return false;
		}
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pmuD = (struct MessageUnit_D *)dma_coherent;
		arcmsr_hbaD_assign_regAddr(acb);
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
		uint32_t completeQ_size;
		completeQ_size = sizeof(struct deliver_completeQ) * ARCMSR_MAX_HBE_DONEQUEUE + 128;
		acb->ioqueue_size = roundup(completeQ_size, 32);
		dma_coherent = dma_alloc_coherent(&pdev->dev, acb->ioqueue_size,
			&dma_coherent_handle, GFP_KERNEL);
		if (!dma_coherent){
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			return false;
		}
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pCompletionQ = dma_coherent;
		acb->completionQ_entry = acb->ioqueue_size / sizeof(struct deliver_completeQ);
		acb->doneq_index = 0;
		}
		break;
	default:
		break;
	}
	return rtn;
}