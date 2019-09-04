#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/ * mapping; } ;
struct msc_window {int nr_blocks; TYPE_2__* block; int /*<<< orphan*/  msc; int /*<<< orphan*/  entry; } ;
struct msc {int nr_pages; scalar_t__ base_addr; int /*<<< orphan*/ * base; int /*<<< orphan*/  win_list; } ;
struct TYPE_6__ {TYPE_1__* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bdesc; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msc_window*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 TYPE_3__* msc_dev (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msc_buffer_win_free(struct msc *msc, struct msc_window *win)
{
	int i;

	msc->nr_pages -= win->nr_blocks;

	list_del(&win->entry);
	if (list_empty(&msc->win_list)) {
		msc->base = NULL;
		msc->base_addr = 0;
	}

	for (i = 0; i < win->nr_blocks; i++) {
		struct page *page = virt_to_page(win->block[i].bdesc);

		page->mapping = NULL;
#ifdef CONFIG_X86
		/* Reset the page to write-back before releasing */
		set_memory_wb((unsigned long)win->block[i].bdesc, 1);
#endif
		dma_free_coherent(msc_dev(win->msc)->parent->parent, PAGE_SIZE,
				  win->block[i].bdesc, win->block[i].addr);
	}

	kfree(win);
}