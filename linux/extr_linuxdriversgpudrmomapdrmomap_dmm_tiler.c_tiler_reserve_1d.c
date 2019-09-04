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
struct tiler_block {size_t fmt; int /*<<< orphan*/  alloc_node; int /*<<< orphan*/  area; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tiler_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 size_t TILFMT_PAGE ; 
 int /*<<< orphan*/ * containers ; 
 int /*<<< orphan*/  kfree (struct tiler_block*) ; 
 struct tiler_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 TYPE_1__* omap_dmm ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tcm_reserve_1d (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

struct tiler_block *tiler_reserve_1d(size_t size)
{
	struct tiler_block *block = kzalloc(sizeof(*block), GFP_KERNEL);
	int num_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned long flags;

	if (!block)
		return ERR_PTR(-ENOMEM);

	block->fmt = TILFMT_PAGE;

	if (tcm_reserve_1d(containers[TILFMT_PAGE], num_pages,
				&block->area)) {
		kfree(block);
		return ERR_PTR(-ENOMEM);
	}

	spin_lock_irqsave(&list_lock, flags);
	list_add(&block->alloc_node, &omap_dmm->alloc_head);
	spin_unlock_irqrestore(&list_lock, flags);

	return block;
}