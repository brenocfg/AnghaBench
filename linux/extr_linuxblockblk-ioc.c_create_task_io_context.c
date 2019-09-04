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
struct task_struct {int flags; struct io_context* io_context; } ;
struct io_context {int /*<<< orphan*/  release_work; int /*<<< orphan*/  icq_list; int /*<<< orphan*/  icq_tree; int /*<<< orphan*/  lock; int /*<<< orphan*/  active_ref; int /*<<< orphan*/  nr_tasks; int /*<<< orphan*/  refcount; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PF_EXITING ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  ioc_release_fn ; 
 int /*<<< orphan*/  iocontext_cachep ; 
 struct io_context* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct io_context*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int create_task_io_context(struct task_struct *task, gfp_t gfp_flags, int node)
{
	struct io_context *ioc;
	int ret;

	ioc = kmem_cache_alloc_node(iocontext_cachep, gfp_flags | __GFP_ZERO,
				    node);
	if (unlikely(!ioc))
		return -ENOMEM;

	/* initialize */
	atomic_long_set(&ioc->refcount, 1);
	atomic_set(&ioc->nr_tasks, 1);
	atomic_set(&ioc->active_ref, 1);
	spin_lock_init(&ioc->lock);
	INIT_RADIX_TREE(&ioc->icq_tree, GFP_ATOMIC);
	INIT_HLIST_HEAD(&ioc->icq_list);
	INIT_WORK(&ioc->release_work, ioc_release_fn);

	/*
	 * Try to install.  ioc shouldn't be installed if someone else
	 * already did or @task, which isn't %current, is exiting.  Note
	 * that we need to allow ioc creation on exiting %current as exit
	 * path may issue IOs from e.g. exit_files().  The exit path is
	 * responsible for not issuing IO after exit_io_context().
	 */
	task_lock(task);
	if (!task->io_context &&
	    (task == current || !(task->flags & PF_EXITING)))
		task->io_context = ioc;
	else
		kmem_cache_free(iocontext_cachep, ioc);

	ret = task->io_context ? 0 : -EBUSY;

	task_unlock(task);

	return ret;
}