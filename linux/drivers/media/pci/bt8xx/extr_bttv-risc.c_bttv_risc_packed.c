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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci; } ;
struct bttv {scalar_t__ opt_vcr_hack; TYPE_1__ c; } ;
struct btcx_riscmem {int size; int /*<<< orphan*/ * cpu; int /*<<< orphan*/ * jmp; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int BT848_FIFO_STATUS_FM1 ; 
 unsigned int BT848_RISC_EOL ; 
 unsigned int BT848_RISC_SKIP ; 
 unsigned int BT848_RISC_SOL ; 
 unsigned int BT848_RISC_SYNC ; 
 unsigned int BT848_RISC_WRITE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PAGE_SIZE ; 
 unsigned int VCR_HACK_LINES ; 
 int btcx_riscmem_alloc (int /*<<< orphan*/ ,struct btcx_riscmem*,int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

int
bttv_risc_packed(struct bttv *btv, struct btcx_riscmem *risc,
		 struct scatterlist *sglist,
		 unsigned int offset, unsigned int bpl,
		 unsigned int padding, unsigned int skip_lines,
		 unsigned int store_lines)
{
	u32 instructions,line,todo;
	struct scatterlist *sg;
	__le32 *rp;
	int rc;

	/* estimate risc mem: worst case is one write per page border +
	   one write per scan line + sync + jump (all 2 dwords).  padding
	   can cause next bpl to start close to a page border.  First DMA
	   region may be smaller than PAGE_SIZE */
	instructions  = skip_lines * 4;
	instructions += (1 + ((bpl + padding) * store_lines)
			 / PAGE_SIZE + store_lines) * 8;
	instructions += 2 * 8;
	if ((rc = btcx_riscmem_alloc(btv->c.pci,risc,instructions)) < 0)
		return rc;

	/* sync instruction */
	rp = risc->cpu;
	*(rp++) = cpu_to_le32(BT848_RISC_SYNC|BT848_FIFO_STATUS_FM1);
	*(rp++) = cpu_to_le32(0);

	while (skip_lines-- > 0) {
		*(rp++) = cpu_to_le32(BT848_RISC_SKIP | BT848_RISC_SOL |
				      BT848_RISC_EOL | bpl);
	}

	/* scan lines */
	sg = sglist;
	for (line = 0; line < store_lines; line++) {
		if ((btv->opt_vcr_hack) &&
		    (line >= (store_lines - VCR_HACK_LINES)))
			continue;
		while (offset && offset >= sg_dma_len(sg)) {
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		}
		if (bpl <= sg_dma_len(sg)-offset) {
			/* fits into current chunk */
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_SOL|
					    BT848_RISC_EOL|bpl);
			*(rp++)=cpu_to_le32(sg_dma_address(sg)+offset);
			offset+=bpl;
		} else {
			/* scanline needs to be split */
			todo = bpl;
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_SOL|
					    (sg_dma_len(sg)-offset));
			*(rp++)=cpu_to_le32(sg_dma_address(sg)+offset);
			todo -= (sg_dma_len(sg)-offset);
			offset = 0;
			sg = sg_next(sg);
			while (todo > sg_dma_len(sg)) {
				*(rp++)=cpu_to_le32(BT848_RISC_WRITE|
						    sg_dma_len(sg));
				*(rp++)=cpu_to_le32(sg_dma_address(sg));
				todo -= sg_dma_len(sg);
				sg = sg_next(sg);
			}
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_EOL|
					    todo);
			*(rp++)=cpu_to_le32(sg_dma_address(sg));
			offset += todo;
		}
		offset += padding;
	}

	/* save pointer to jmp instruction address */
	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * sizeof(*risc->cpu) > risc->size);
	return 0;
}