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
struct scatterlist {scalar_t__ offset; int length; } ;
struct saa7146_pgtable {scalar_t__ offset; int /*<<< orphan*/ * cpu; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 

int saa7146_pgtable_build_single(struct pci_dev *pci, struct saa7146_pgtable *pt,
	struct scatterlist *list, int sglen  )
{
	__le32 *ptr, fill;
	int nr_pages = 0;
	int i,p;

	BUG_ON(0 == sglen);
	BUG_ON(list->offset > PAGE_SIZE);

	/* if we have a user buffer, the first page may not be
	   aligned to a page boundary. */
	pt->offset = list->offset;

	ptr = pt->cpu;
	for (i = 0; i < sglen; i++, list++) {
/*
		pr_debug("i:%d, adr:0x%08x, len:%d, offset:%d\n",
			 i, sg_dma_address(list), sg_dma_len(list),
			 list->offset);
*/
		for (p = 0; p * 4096 < list->length; p++, ptr++) {
			*ptr = cpu_to_le32(sg_dma_address(list) + p * 4096);
			nr_pages++;
		}
	}


	/* safety; fill the page table up with the last valid page */
	fill = *(ptr-1);
	for(i=nr_pages;i<1024;i++) {
		*ptr++ = fill;
	}

/*
	ptr = pt->cpu;
	pr_debug("offset: %d\n", pt->offset);
	for(i=0;i<5;i++) {
		pr_debug("ptr1 %d: 0x%08x\n", i, ptr[i]);
	}
*/
	return 0;
}