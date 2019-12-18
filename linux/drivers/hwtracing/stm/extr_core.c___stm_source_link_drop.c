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
struct TYPE_6__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  master; } ;
struct stm_source_device {TYPE_3__ output; TYPE_2__* data; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  link; int /*<<< orphan*/  link_entry; } ;
struct stm_device {TYPE_1__* data; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  link_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* unlink ) (TYPE_2__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* unlink ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct stm_device* srcu_dereference_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm_output_free (struct stm_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  stm_put_device (struct stm_device*) ; 
 int /*<<< orphan*/  stm_source_srcu ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __stm_source_link_drop(struct stm_source_device *src,
				  struct stm_device *stm)
{
	struct stm_device *link;
	int ret = 0;

	lockdep_assert_held(&stm->link_mutex);

	/* for stm::link_list modification, we hold both mutex and spinlock */
	spin_lock(&stm->link_lock);
	spin_lock(&src->link_lock);
	link = srcu_dereference_check(src->link, &stm_source_srcu, 1);

	/*
	 * The linked device may have changed since we last looked, because
	 * we weren't holding the src::link_lock back then; if this is the
	 * case, tell the caller to retry.
	 */
	if (link != stm) {
		ret = -EAGAIN;
		goto unlock;
	}

	stm_output_free(link, &src->output);
	list_del_init(&src->link_entry);
	pm_runtime_mark_last_busy(&link->dev);
	pm_runtime_put_autosuspend(&link->dev);
	/* matches stm_find_device() from stm_source_link_store() */
	stm_put_device(link);
	rcu_assign_pointer(src->link, NULL);

unlock:
	spin_unlock(&src->link_lock);
	spin_unlock(&stm->link_lock);

	/*
	 * Call the unlink callbacks for both source and stm, when we know
	 * that we have actually performed the unlinking.
	 */
	if (!ret) {
		if (src->data->unlink)
			src->data->unlink(src->data);

		if (stm->data->unlink)
			stm->data->unlink(stm->data, src->output.master,
					  src->output.channel);
	}

	return ret;
}