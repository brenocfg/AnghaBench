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
struct cx25821_riscmem {int size; int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * jmp; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NO_SYNC_LINE ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/ * cx25821_risc_field_audio (int /*<<< orphan*/ *,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int cx25821_riscmem_alloc (struct pci_dev*,struct cx25821_riscmem*,int) ; 

int cx25821_risc_databuffer_audio(struct pci_dev *pci,
				  struct cx25821_riscmem *risc,
				  struct scatterlist *sglist,
				  unsigned int bpl,
				  unsigned int lines, unsigned int lpi)
{
	u32 instructions;
	__le32 *rp;
	int rc;

	/* estimate risc mem: worst case is one write per page border +
	   one write per scan line + syncs + jump (all 2 dwords).  Here
	   there is no padding and no sync.  First DMA region may be smaller
	   than PAGE_SIZE */
	/* Jump and write need an extra dword */
	instructions = 1 + (bpl * lines) / PAGE_SIZE + lines;
	instructions += 1;

	rc = cx25821_riscmem_alloc(pci, risc, instructions * 12);
	if (rc < 0)
		return rc;

	/* write risc instructions */
	rp = risc->cpu;
	rp = cx25821_risc_field_audio(rp, sglist, 0, NO_SYNC_LINE, bpl, 0,
				      lines, lpi);

	/* save pointer to jmp instruction address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * sizeof(*risc->cpu) > risc->size);
	return 0;
}