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
struct msc_iter {int /*<<< orphan*/  entry; } ;
struct msc {int /*<<< orphan*/  buf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct msc_iter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msc_iter_remove(struct msc_iter *iter, struct msc *msc)
{
	mutex_lock(&msc->buf_mutex);
	list_del(&iter->entry);
	mutex_unlock(&msc->buf_mutex);

	kfree(iter);
}