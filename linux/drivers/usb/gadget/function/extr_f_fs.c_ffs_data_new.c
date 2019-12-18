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
struct TYPE_2__ {int can_stall; int /*<<< orphan*/  waitq; } ;
struct ffs_data {TYPE_1__ ev; int /*<<< orphan*/  ep0req_completion; int /*<<< orphan*/  wait; int /*<<< orphan*/  eps_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  opened; int /*<<< orphan*/  ref; int /*<<< orphan*/  io_completion_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  FFS_READ_DESCRIPTORS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ffs_data*) ; 
 struct ffs_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ffs_data *ffs_data_new(const char *dev_name)
{
	struct ffs_data *ffs = kzalloc(sizeof *ffs, GFP_KERNEL);
	if (unlikely(!ffs))
		return NULL;

	ENTER();

	ffs->io_completion_wq = alloc_ordered_workqueue("%s", 0, dev_name);
	if (!ffs->io_completion_wq) {
		kfree(ffs);
		return NULL;
	}

	refcount_set(&ffs->ref, 1);
	atomic_set(&ffs->opened, 0);
	ffs->state = FFS_READ_DESCRIPTORS;
	mutex_init(&ffs->mutex);
	spin_lock_init(&ffs->eps_lock);
	init_waitqueue_head(&ffs->ev.waitq);
	init_waitqueue_head(&ffs->wait);
	init_completion(&ffs->ep0req_completion);

	/* XXX REVISIT need to update it in some places, or do we? */
	ffs->ev.can_stall = 1;

	return ffs;
}