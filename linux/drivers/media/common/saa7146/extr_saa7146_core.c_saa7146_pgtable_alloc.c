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
struct saa7146_pgtable {int /*<<< orphan*/  dma; int /*<<< orphan*/ * cpu; int /*<<< orphan*/  size; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * pci_alloc_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int saa7146_pgtable_alloc(struct pci_dev *pci, struct saa7146_pgtable *pt)
{
	__le32       *cpu;
	dma_addr_t   dma_addr = 0;

	cpu = pci_alloc_consistent(pci, PAGE_SIZE, &dma_addr);
	if (NULL == cpu) {
		return -ENOMEM;
	}
	pt->size = PAGE_SIZE;
	pt->cpu  = cpu;
	pt->dma  = dma_addr;

	return 0;
}