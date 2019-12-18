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
struct msc_window {int /*<<< orphan*/  sgt; int /*<<< orphan*/  entry; scalar_t__ nr_blocks; } ;
struct msc {int /*<<< orphan*/  mbuf_priv; TYPE_1__* mbuf; scalar_t__ base_addr; int /*<<< orphan*/ * base; int /*<<< orphan*/  win_list; int /*<<< orphan*/  nr_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_window ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __msc_buffer_win_free (struct msc*,struct msc_window*) ; 
 int /*<<< orphan*/  kfree (struct msc_window*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msc_buffer_set_wb (struct msc_window*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msc_buffer_win_free(struct msc *msc, struct msc_window *win)
{
	msc->nr_pages -= win->nr_blocks;

	list_del(&win->entry);
	if (list_empty(&msc->win_list)) {
		msc->base = NULL;
		msc->base_addr = 0;
	}

	msc_buffer_set_wb(win);

	if (msc->mbuf && msc->mbuf->free_window)
		msc->mbuf->free_window(msc->mbuf_priv, win->sgt);
	else
		__msc_buffer_win_free(msc, win);

	kfree(win);
}