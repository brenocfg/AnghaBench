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
 int /*<<< orphan*/  DBG_RES (char*,int,unsigned int,unsigned int) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  PCXL_FIND_FREE_MAPPING (int,unsigned int,int) ; 
 int /*<<< orphan*/  dump_resmap () ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 unsigned long pcxl_dma_start ; 
 unsigned int pcxl_res_hint ; 
 int /*<<< orphan*/  pcxl_res_lock ; 
 unsigned int pcxl_used_bytes ; 
 unsigned int pcxl_used_pages ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned int) ; 

unsigned long
pcxl_alloc_range(size_t size)
{
	int res_idx;
	u_long mask, flags;
	unsigned int pages_needed = size >> PAGE_SHIFT;

	mask = (u_long) -1L;
 	mask >>= BITS_PER_LONG - pages_needed;

	DBG_RES("pcxl_alloc_range() size: %d pages_needed %d pages_mask 0x%08lx\n", 
		size, pages_needed, mask);

	spin_lock_irqsave(&pcxl_res_lock, flags);

	if(pages_needed <= 8) {
		PCXL_FIND_FREE_MAPPING(res_idx, mask, 8);
	} else if(pages_needed <= 16) {
		PCXL_FIND_FREE_MAPPING(res_idx, mask, 16);
	} else if(pages_needed <= 32) {
		PCXL_FIND_FREE_MAPPING(res_idx, mask, 32);
	} else {
		panic("%s: pcxl_alloc_range() Too many pages to map.\n",
		      __FILE__);
	}

	dump_resmap();
	panic("%s: pcxl_alloc_range() out of dma mapping resources\n",
	      __FILE__);
	
resource_found:
	
	DBG_RES("pcxl_alloc_range() res_idx %d mask 0x%08lx res_hint: %d\n",
		res_idx, mask, pcxl_res_hint);

	pcxl_used_pages += pages_needed;
	pcxl_used_bytes += ((pages_needed >> 3) ? (pages_needed >> 3) : 1);

	spin_unlock_irqrestore(&pcxl_res_lock, flags);

	dump_resmap();

	/* 
	** return the corresponding vaddr in the pcxl dma map
	*/
	return (pcxl_dma_start + (res_idx << (PAGE_SHIFT + 3)));
}