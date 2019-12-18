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
struct AdapterControlBlock {int adapter_type; int /*<<< orphan*/  dma_coherent_handle2; int /*<<< orphan*/  dma_coherent2; int /*<<< orphan*/  ioqueue_size; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_B 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_free_io_queue(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_B:
	case ACB_ADAPTER_TYPE_D:
	case ACB_ADAPTER_TYPE_E: {
		dma_free_coherent(&acb->pdev->dev, acb->ioqueue_size,
			acb->dma_coherent2, acb->dma_coherent_handle2);
		break;
	}
	}
}