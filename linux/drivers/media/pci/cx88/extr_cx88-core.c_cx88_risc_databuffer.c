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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct pci_dev {int dummy; } ;
struct cx88_riscmem {int size; int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * jmp; scalar_t__ dma; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_LINE ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * cx88_risc_field (int /*<<< orphan*/ *,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/ * pci_zalloc_consistent (struct pci_dev*,int,scalar_t__*) ; 

int cx88_risc_databuffer(struct pci_dev *pci, struct cx88_riscmem *risc,
			 struct scatterlist *sglist, unsigned int bpl,
			 unsigned int lines, unsigned int lpi)
{
	u32 instructions;
	__le32 *rp;

	/*
	 * estimate risc mem: worst case is one write per page border +
	 * one write per scan line + syncs + jump (all 2 dwords).  Here
	 * there is no padding and no sync.  First DMA region may be smaller
	 * than PAGE_SIZE
	 */
	instructions  = 1 + (bpl * lines) / PAGE_SIZE + lines;
	instructions += 3;
	risc->size = instructions * 8;
	risc->dma = 0;
	risc->cpu = pci_zalloc_consistent(pci, risc->size, &risc->dma);
	if (!risc->cpu)
		return -ENOMEM;

	/* write risc instructions */
	rp = risc->cpu;
	rp = cx88_risc_field(rp, sglist, 0, NO_SYNC_LINE, bpl, 0,
			     lines, lpi, !lpi);

	/* save pointer to jmp instruction address */
	risc->jmp = rp;
	WARN_ON((risc->jmp - risc->cpu + 2) * sizeof(*risc->cpu) > risc->size);
	return 0;
}