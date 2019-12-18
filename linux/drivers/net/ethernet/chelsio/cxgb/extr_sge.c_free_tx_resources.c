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
struct sge {struct cmdQ* cmdQ; TYPE_1__* adapter; } ;
struct pci_dev {int dummy; } ;
struct cmdQ_e {int dummy; } ;
struct cmdQ {int size; int /*<<< orphan*/  dma_addr; scalar_t__ entries; scalar_t__ centries; scalar_t__ in_use; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 unsigned int SGE_CMDQ_N ; 
 int /*<<< orphan*/  free_cmdQ_buffers (struct sge*,struct cmdQ*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_tx_resources(struct sge *sge)
{
	struct pci_dev *pdev = sge->adapter->pdev;
	unsigned int size, i;

	for (i = 0; i < SGE_CMDQ_N; i++) {
		struct cmdQ *q = &sge->cmdQ[i];

		if (q->centries) {
			if (q->in_use)
				free_cmdQ_buffers(sge, q, q->in_use);
			kfree(q->centries);
		}
		if (q->entries) {
			size = sizeof(struct cmdQ_e) * q->size;
			pci_free_consistent(pdev, size, q->entries,
					    q->dma_addr);
		}
	}
}