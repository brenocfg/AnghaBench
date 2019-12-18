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
typedef  int u64 ;
struct rx_ring_info {int rbr_blocks_per_page; scalar_t__ rbr_block_size; int /*<<< orphan*/ * rbr; } ;
struct page {int dummy; } ;
struct niu {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int (* map_page ) (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RBR_DESCR_ADDR_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  niu_hash_page (struct rx_ring_info*,struct page*,int) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_rbr_add_page(struct niu *np, struct rx_ring_info *rp,
			    gfp_t mask, int start_index)
{
	struct page *page;
	u64 addr;
	int i;

	page = alloc_page(mask);
	if (!page)
		return -ENOMEM;

	addr = np->ops->map_page(np->device, page, 0,
				 PAGE_SIZE, DMA_FROM_DEVICE);
	if (!addr) {
		__free_page(page);
		return -ENOMEM;
	}

	niu_hash_page(rp, page, addr);
	if (rp->rbr_blocks_per_page > 1)
		page_ref_add(page, rp->rbr_blocks_per_page - 1);

	for (i = 0; i < rp->rbr_blocks_per_page; i++) {
		__le32 *rbr = &rp->rbr[start_index + i];

		*rbr = cpu_to_le32(addr >> RBR_DESCR_ADDR_SHIFT);
		addr += rp->rbr_block_size;
	}

	return 0;
}