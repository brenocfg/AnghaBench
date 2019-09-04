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
struct TYPE_4__ {int size; int /*<<< orphan*/  dma_addr; scalar_t__ entries; } ;
struct sge {struct freelQ* freelQ; TYPE_2__ respQ; TYPE_1__* adapter; } ;
struct respQ_e {int dummy; } ;
struct pci_dev {int dummy; } ;
struct freelQ_e {int dummy; } ;
struct freelQ {int size; int /*<<< orphan*/  dma_addr; scalar_t__ entries; scalar_t__ centries; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 unsigned int SGE_FREELQ_N ; 
 int /*<<< orphan*/  free_freelQ_buffers (struct pci_dev*,struct freelQ*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rx_resources(struct sge *sge)
{
	struct pci_dev *pdev = sge->adapter->pdev;
	unsigned int size, i;

	if (sge->respQ.entries) {
		size = sizeof(struct respQ_e) * sge->respQ.size;
		pci_free_consistent(pdev, size, sge->respQ.entries,
				    sge->respQ.dma_addr);
	}

	for (i = 0; i < SGE_FREELQ_N; i++) {
		struct freelQ *q = &sge->freelQ[i];

		if (q->centries) {
			free_freelQ_buffers(pdev, q);
			kfree(q->centries);
		}
		if (q->entries) {
			size = sizeof(struct freelQ_e) * q->size;
			pci_free_consistent(pdev, size, q->entries,
					    q->dma_addr);
		}
	}
}