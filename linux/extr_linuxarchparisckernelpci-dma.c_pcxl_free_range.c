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
typedef  unsigned int u_long ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 int /*<<< orphan*/  DBG_RES (char*,unsigned int,size_t,unsigned int,unsigned int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PCXL_FREE_MAPPINGS (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  dump_resmap () ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 unsigned long pcxl_dma_start ; 
 int /*<<< orphan*/  pcxl_res_lock ; 
 unsigned int pcxl_used_bytes ; 
 unsigned int pcxl_used_pages ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
pcxl_free_range(unsigned long vaddr, size_t size)
{
	u_long mask, flags;
	unsigned int res_idx = (vaddr - pcxl_dma_start) >> (PAGE_SHIFT + 3);
	unsigned int pages_mapped = size >> PAGE_SHIFT;

	mask = (u_long) -1L;
 	mask >>= BITS_PER_LONG - pages_mapped;

	DBG_RES("pcxl_free_range() res_idx: %d size: %d pages_mapped %d mask 0x%08lx\n", 
		res_idx, size, pages_mapped, mask);

	spin_lock_irqsave(&pcxl_res_lock, flags);

	if(pages_mapped <= 8) {
		PCXL_FREE_MAPPINGS(res_idx, mask, 8);
	} else if(pages_mapped <= 16) {
		PCXL_FREE_MAPPINGS(res_idx, mask, 16);
	} else if(pages_mapped <= 32) {
		PCXL_FREE_MAPPINGS(res_idx, mask, 32);
	} else {
		panic("%s: pcxl_free_range() Too many pages to unmap.\n",
		      __FILE__);
	}
	
	pcxl_used_pages -= (pages_mapped ? pages_mapped : 1);
	pcxl_used_bytes -= ((pages_mapped >> 3) ? (pages_mapped >> 3) : 1);

	spin_unlock_irqrestore(&pcxl_res_lock, flags);

	dump_resmap();
}