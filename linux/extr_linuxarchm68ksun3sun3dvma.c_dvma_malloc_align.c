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

/* Variables and functions */
 unsigned long DVMA_PAGE_MASK ; 
 int DVMA_PAGE_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long dvma_btov (unsigned long) ; 
 scalar_t__ dvma_map_align (unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ dvma_map_cpu (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dvma_unmap (void*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,...) ; 

void *dvma_malloc_align(unsigned long len, unsigned long align)
{
	unsigned long kaddr;
	unsigned long baddr;
	unsigned long vaddr;

	if(!len)
		return NULL;

	pr_debug("dvma_malloc request %lx bytes\n", len);
	len = ((len + (DVMA_PAGE_SIZE-1)) & DVMA_PAGE_MASK);

        if((kaddr = __get_free_pages(GFP_ATOMIC, get_order(len))) == 0)
		return NULL;

	if((baddr = (unsigned long)dvma_map_align(kaddr, len, align)) == 0) {
		free_pages(kaddr, get_order(len));
		return NULL;
	}

	vaddr = dvma_btov(baddr);

	if(dvma_map_cpu(kaddr, vaddr, len) < 0) {
		dvma_unmap((void *)baddr);
		free_pages(kaddr, get_order(len));
		return NULL;
	}

	pr_debug("mapped %08lx bytes %08lx kern -> %08lx bus\n", len, kaddr,
		 baddr);

	return (void *)vaddr;

}