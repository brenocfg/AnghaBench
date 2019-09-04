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
typedef  unsigned int u32 ;
struct sg_entry {void* flags; void* len; void* target_addr; } ;
struct genwqe_sgl {size_t user_size; unsigned long fpage_offs; int nr_pages; scalar_t__ sgl_dma_addr; scalar_t__ fpage_dma_addr; scalar_t__ lpage_dma_addr; int /*<<< orphan*/ * lpage; int /*<<< orphan*/ * fpage; struct sg_entry* sgl; } ;
struct genwqe_dev {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 unsigned int SG_CHAINED ; 
 unsigned int SG_DATA ; 
 unsigned int SG_END_LIST ; 
 unsigned int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (unsigned int) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 unsigned int min (size_t,scalar_t__) ; 

int genwqe_setup_sgl(struct genwqe_dev *cd, struct genwqe_sgl *sgl,
		     dma_addr_t *dma_list)
{
	int i = 0, j = 0, p;
	unsigned long dma_offs, map_offs;
	dma_addr_t prev_daddr = 0;
	struct sg_entry *s, *last_s = NULL;
	size_t size = sgl->user_size;

	dma_offs = 128;		/* next block if needed/dma_offset */
	map_offs = sgl->fpage_offs; /* offset in first page */

	s = &sgl->sgl[0];	/* first set of 8 entries */
	p = 0;			/* page */
	while (p < sgl->nr_pages) {
		dma_addr_t daddr;
		unsigned int size_to_map;

		/* always write the chaining entry, cleanup is done later */
		j = 0;
		s[j].target_addr = cpu_to_be64(sgl->sgl_dma_addr + dma_offs);
		s[j].len	 = cpu_to_be32(128);
		s[j].flags	 = cpu_to_be32(SG_CHAINED);
		j++;

		while (j < 8) {
			/* DMA mapping for requested page, offs, size */
			size_to_map = min(size, PAGE_SIZE - map_offs);

			if ((p == 0) && (sgl->fpage != NULL)) {
				daddr = sgl->fpage_dma_addr + map_offs;

			} else if ((p == sgl->nr_pages - 1) &&
				   (sgl->lpage != NULL)) {
				daddr = sgl->lpage_dma_addr;
			} else {
				daddr = dma_list[p] + map_offs;
			}

			size -= size_to_map;
			map_offs = 0;

			if (prev_daddr == daddr) {
				u32 prev_len = be32_to_cpu(last_s->len);

				/* pr_info("daddr combining: "
					"%016llx/%08x -> %016llx\n",
					prev_daddr, prev_len, daddr); */

				last_s->len = cpu_to_be32(prev_len +
							  size_to_map);

				p++; /* process next page */
				if (p == sgl->nr_pages)
					goto fixup;  /* nothing to do */

				prev_daddr = daddr + size_to_map;
				continue;
			}

			/* start new entry */
			s[j].target_addr = cpu_to_be64(daddr);
			s[j].len	 = cpu_to_be32(size_to_map);
			s[j].flags	 = cpu_to_be32(SG_DATA);
			prev_daddr = daddr + size_to_map;
			last_s = &s[j];
			j++;

			p++;	/* process next page */
			if (p == sgl->nr_pages)
				goto fixup;  /* nothing to do */
		}
		dma_offs += 128;
		s += 8;		/* continue 8 elements further */
	}
 fixup:
	if (j == 1) {		/* combining happened on last entry! */
		s -= 8;		/* full shift needed on previous sgl block */
		j =  7;		/* shift all elements */
	}

	for (i = 0; i < j; i++)	/* move elements 1 up */
		s[i] = s[i + 1];

	s[i].target_addr = cpu_to_be64(0);
	s[i].len	 = cpu_to_be32(0);
	s[i].flags	 = cpu_to_be32(SG_END_LIST);
	return 0;
}