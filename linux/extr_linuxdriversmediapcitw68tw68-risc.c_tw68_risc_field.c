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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int RISC_INLINE ; 
 unsigned int RISC_JUMP ; 
 unsigned int RISC_LINESTART ; 
 unsigned int RISC_SYNCE ; 
 unsigned int RISC_SYNCO ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static __le32 *tw68_risc_field(__le32 *rp, struct scatterlist *sglist,
			    unsigned int offset, u32 sync_line,
			    unsigned int bpl, unsigned int padding,
			    unsigned int lines, bool jump)
{
	struct scatterlist *sg;
	unsigned int line, todo, done;

	if (jump) {
		*(rp++) = cpu_to_le32(RISC_JUMP);
		*(rp++) = 0;
	}

	/* sync instruction */
	if (sync_line == 1)
		*(rp++) = cpu_to_le32(RISC_SYNCO);
	else
		*(rp++) = cpu_to_le32(RISC_SYNCE);
	*(rp++) = 0;

	/* scan lines */
	sg = sglist;
	for (line = 0; line < lines; line++) {
		/* calculate next starting position */
		while (offset && offset >= sg_dma_len(sg)) {
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		}
		if (bpl <= sg_dma_len(sg) - offset) {
			/* fits into current chunk */
			*(rp++) = cpu_to_le32(RISC_LINESTART |
					      /* (offset<<12) |*/  bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			offset += bpl;
		} else {
			/*
			 * scanline needs to be split.  Put the start in
			 * whatever memory remains using RISC_LINESTART,
			 * then the remainder into following addresses
			 * given by the scatter-gather list.
			 */
			todo = bpl;	/* one full line to be done */
			/* first fragment */
			done = (sg_dma_len(sg) - offset);
			*(rp++) = cpu_to_le32(RISC_LINESTART |
						(7 << 24) |
						done);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			todo -= done;
			sg = sg_next(sg);
			/* succeeding fragments have no offset */
			while (todo > sg_dma_len(sg)) {
				*(rp++) = cpu_to_le32(RISC_INLINE |
						(done << 12) |
						sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				todo -= sg_dma_len(sg);
				sg = sg_next(sg);
				done += sg_dma_len(sg);
			}
			if (todo) {
				/* final chunk - offset 0, count 'todo' */
				*(rp++) = cpu_to_le32(RISC_INLINE |
							(done << 12) |
							todo);
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
			}
			offset = todo;
		}
		offset += padding;
	}

	return rp;
}