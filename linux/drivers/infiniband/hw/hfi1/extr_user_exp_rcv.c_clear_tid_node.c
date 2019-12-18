#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct tid_rb_node {int rcventry; TYPE_2__* grp; int /*<<< orphan*/  npages; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  phys; TYPE_1__ mmu; } ;
struct hfi1_filedata {int /*<<< orphan*/  subctxt; struct hfi1_ctxtdata* uctxt; } ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  tid_group_list; int /*<<< orphan*/  tid_used_list; int /*<<< orphan*/  tid_full_list; int /*<<< orphan*/  ctxt; struct hfi1_devdata* dd; } ;
struct TYPE_4__ {int used; int map; int base; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_INVALID_FLUSH ; 
 int /*<<< orphan*/  hfi1_put_tid (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tid_rb_node*) ; 
 int /*<<< orphan*/  tid_group_move (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hfi1_exp_tid_unreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpin_rcv_pages (struct hfi1_filedata*,int /*<<< orphan*/ *,struct tid_rb_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_tid_node(struct hfi1_filedata *fd, struct tid_rb_node *node)
{
	struct hfi1_ctxtdata *uctxt = fd->uctxt;
	struct hfi1_devdata *dd = uctxt->dd;

	trace_hfi1_exp_tid_unreg(uctxt->ctxt, fd->subctxt, node->rcventry,
				 node->npages, node->mmu.addr, node->phys,
				 node->dma_addr);

	/*
	 * Make sure device has seen the write before we unpin the
	 * pages.
	 */
	hfi1_put_tid(dd, node->rcventry, PT_INVALID_FLUSH, 0, 0);

	unpin_rcv_pages(fd, NULL, node, 0, node->npages, true);

	node->grp->used--;
	node->grp->map &= ~(1 << (node->rcventry - node->grp->base));

	if (node->grp->used == node->grp->size - 1)
		tid_group_move(node->grp, &uctxt->tid_full_list,
			       &uctxt->tid_used_list);
	else if (!node->grp->used)
		tid_group_move(node->grp, &uctxt->tid_used_list,
			       &uctxt->tid_group_list);
	kfree(node);
}