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
 unsigned int PAGE_SIZE ; 
 unsigned int UNSET ; 
 int /*<<< orphan*/ * cx25821_risc_field (int /*<<< orphan*/ *,struct scatterlist*,unsigned int,int,unsigned int,unsigned int,unsigned int,int) ; 
 int cx25821_riscmem_alloc (struct pci_dev*,struct cx25821_riscmem*,int) ; 

int cx25821_risc_buffer(struct pci_dev *pci, struct cx25821_riscmem *risc,
			struct scatterlist *sglist, unsigned int top_offset,
			unsigned int bottom_offset, unsigned int bpl,
			unsigned int padding, unsigned int lines)
{
	u32 instructions;
	u32 fields;
	__le32 *rp;
	int rc;

	fields = 0;
	if (UNSET != top_offset)
		fields++;
	if (UNSET != bottom_offset)
		fields++;

	/* estimate risc mem: worst case is one write per page border +
	   one write per scan line + syncs + jump (all 3 dwords).  Padding
	   can cause next bpl to start close to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	/* write and jump need and extra dword */
	instructions = fields * (1 + ((bpl + padding) * lines) / PAGE_SIZE +
			lines);
	instructions += 5;
	rc = cx25821_riscmem_alloc(pci, risc, instructions * 12);

	if (rc < 0)
		return rc;

	/* write risc instructions */
	rp = risc->cpu;

	if (UNSET != top_offset) {
		rp = cx25821_risc_field(rp, sglist, top_offset, 0, bpl, padding,
					lines, true);
	}

	if (UNSET != bottom_offset) {
		rp = cx25821_risc_field(rp, sglist, bottom_offset, 0x200, bpl,
					padding, lines, UNSET == top_offset);
	}

	/* save pointer to jmp instruction address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 3) * sizeof(*risc->cpu) > risc->size);

	return 0;
}