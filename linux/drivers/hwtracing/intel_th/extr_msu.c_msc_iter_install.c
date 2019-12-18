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
struct msc_iter {int /*<<< orphan*/  entry; struct msc* msc; } ;
struct msc {int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  iter_list; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct msc_iter* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct msc_iter*) ; 
 struct msc_iter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct msc_iter *msc_iter_install(struct msc *msc)
{
	struct msc_iter *iter;

	iter = kzalloc(sizeof(*iter), GFP_KERNEL);
	if (!iter)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&msc->buf_mutex);

	/*
	 * Reading and tracing are mutually exclusive; if msc is
	 * enabled, open() will fail; otherwise existing readers
	 * will prevent enabling the msc and the rest of fops don't
	 * need to worry about it.
	 */
	if (msc->enabled) {
		kfree(iter);
		iter = ERR_PTR(-EBUSY);
		goto unlock;
	}

	iter->msc = msc;

	list_add_tail(&iter->entry, &msc->iter_list);
unlock:
	mutex_unlock(&msc->buf_mutex);

	return iter;
}