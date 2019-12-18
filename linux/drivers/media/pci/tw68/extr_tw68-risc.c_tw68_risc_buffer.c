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
struct tw68_buf {int size; int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * jmp; scalar_t__ dma; } ;
struct scatterlist {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 unsigned int PAGE_SIZE ; 
 unsigned int UNSET ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/ * tw68_risc_field (int /*<<< orphan*/ *,struct scatterlist*,unsigned int,int,unsigned int,unsigned int,unsigned int,int) ; 

int tw68_risc_buffer(struct pci_dev *pci,
			struct tw68_buf *buf,
			struct scatterlist *sglist,
			unsigned int top_offset,
			unsigned int bottom_offset,
			unsigned int bpl,
			unsigned int padding,
			unsigned int lines)
{
	u32 instructions, fields;
	__le32 *rp;

	fields = 0;
	if (UNSET != top_offset)
		fields++;
	if (UNSET != bottom_offset)
		fields++;
	/*
	 * estimate risc mem: worst case is one write per page border +
	 * one write per scan line + syncs + 2 jumps (all 2 dwords).
	 * Padding can cause next bpl to start close to a page border.
	 * First DMA region may be smaller than PAGE_SIZE
	 */
	instructions  = fields * (1 + (((bpl + padding) * lines) /
			 PAGE_SIZE) + lines) + 4;
	buf->size = instructions * 8;
	buf->cpu = pci_alloc_consistent(pci, buf->size, &buf->dma);
	if (buf->cpu == NULL)
		return -ENOMEM;

	/* write risc instructions */
	rp = buf->cpu;
	if (UNSET != top_offset)	/* generates SYNCO */
		rp = tw68_risc_field(rp, sglist, top_offset, 1,
				     bpl, padding, lines, true);
	if (UNSET != bottom_offset)	/* generates SYNCE */
		rp = tw68_risc_field(rp, sglist, bottom_offset, 2,
				     bpl, padding, lines, top_offset == UNSET);

	/* save pointer to jmp instruction address */
	buf->jmp = rp;
	buf->cpu[1] = cpu_to_le32(buf->dma + 8);
	/* assure risc buffer hasn't overflowed */
	BUG_ON((buf->jmp - buf->cpu + 2) * sizeof(buf->cpu[0]) > buf->size);
	return 0;
}