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
struct workqueue_struct {int dummy; } ;
struct mmu_rb_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  hlist; } ;
struct mmu_rb_handler {struct mm_struct* mm; TYPE_1__ mn; struct workqueue_struct* wq; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  del_list; int /*<<< orphan*/  del_work; int /*<<< orphan*/  lock; void* ops_arg; struct mmu_rb_ops* ops; int /*<<< orphan*/  root; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  handle_remove ; 
 int /*<<< orphan*/  kfree (struct mmu_rb_handler*) ; 
 struct mmu_rb_handler* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mmu_notifier_register (TYPE_1__*,struct mm_struct*) ; 
 int /*<<< orphan*/  mn_opts ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hfi1_mmu_rb_register(void *ops_arg, struct mm_struct *mm,
			 struct mmu_rb_ops *ops,
			 struct workqueue_struct *wq,
			 struct mmu_rb_handler **handler)
{
	struct mmu_rb_handler *handlr;
	int ret;

	handlr = kmalloc(sizeof(*handlr), GFP_KERNEL);
	if (!handlr)
		return -ENOMEM;

	handlr->root = RB_ROOT_CACHED;
	handlr->ops = ops;
	handlr->ops_arg = ops_arg;
	INIT_HLIST_NODE(&handlr->mn.hlist);
	spin_lock_init(&handlr->lock);
	handlr->mn.ops = &mn_opts;
	handlr->mm = mm;
	INIT_WORK(&handlr->del_work, handle_remove);
	INIT_LIST_HEAD(&handlr->del_list);
	INIT_LIST_HEAD(&handlr->lru_list);
	handlr->wq = wq;

	ret = mmu_notifier_register(&handlr->mn, handlr->mm);
	if (ret) {
		kfree(handlr);
		return ret;
	}

	*handler = handlr;
	return 0;
}