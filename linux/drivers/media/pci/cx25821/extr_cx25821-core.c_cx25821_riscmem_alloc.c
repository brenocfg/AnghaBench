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
struct pci_dev {int dummy; } ;
struct cx25821_riscmem {unsigned int size; int /*<<< orphan*/  dma; int /*<<< orphan*/ * cpu; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_zalloc_consistent (struct pci_dev*,unsigned int,int /*<<< orphan*/ *) ; 

int cx25821_riscmem_alloc(struct pci_dev *pci,
		       struct cx25821_riscmem *risc,
		       unsigned int size)
{
	__le32 *cpu;
	dma_addr_t dma = 0;

	if (NULL != risc->cpu && risc->size < size)
		pci_free_consistent(pci, risc->size, risc->cpu, risc->dma);
	if (NULL == risc->cpu) {
		cpu = pci_zalloc_consistent(pci, size, &dma);
		if (NULL == cpu)
			return -ENOMEM;
		risc->cpu  = cpu;
		risc->dma  = dma;
		risc->size = size;
	}
	return 0;
}