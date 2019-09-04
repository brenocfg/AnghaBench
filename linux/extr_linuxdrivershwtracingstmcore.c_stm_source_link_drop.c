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
struct stm_source_device {int /*<<< orphan*/  link; } ;
struct stm_device {int /*<<< orphan*/  link_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int __stm_source_link_drop (struct stm_source_device*,struct stm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stm_device* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm_source_srcu ; 

__attribute__((used)) static void stm_source_link_drop(struct stm_source_device *src)
{
	struct stm_device *stm;
	int idx, ret;

retry:
	idx = srcu_read_lock(&stm_source_srcu);
	/*
	 * The stm device will be valid for the duration of this
	 * read section, but the link may change before we grab
	 * the src::link_lock in __stm_source_link_drop().
	 */
	stm = srcu_dereference(src->link, &stm_source_srcu);

	ret = 0;
	if (stm) {
		mutex_lock(&stm->link_mutex);
		ret = __stm_source_link_drop(src, stm);
		mutex_unlock(&stm->link_mutex);
	}

	srcu_read_unlock(&stm_source_srcu, idx);

	/* if it did change, retry */
	if (ret == -EAGAIN)
		goto retry;
}