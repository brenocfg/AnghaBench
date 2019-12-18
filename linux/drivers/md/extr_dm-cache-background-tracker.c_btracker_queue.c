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
struct policy_work {int dummy; } ;
struct bt_work {struct policy_work work; int /*<<< orphan*/  list; } ;
struct background_tracker {int /*<<< orphan*/  queued; int /*<<< orphan*/  issued; int /*<<< orphan*/  work_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __insert_pending (struct background_tracker*,struct bt_work*) ; 
 struct bt_work* alloc_work (struct background_tracker*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bt_work*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct policy_work*,struct policy_work*,int) ; 
 int /*<<< orphan*/  update_stats (struct background_tracker*,struct policy_work*,int) ; 

int btracker_queue(struct background_tracker *b,
		   struct policy_work *work,
		   struct policy_work **pwork)
{
	struct bt_work *w;

	if (pwork)
		*pwork = NULL;

	w = alloc_work(b);
	if (!w)
		return -ENOMEM;

	memcpy(&w->work, work, sizeof(*work));

	if (!__insert_pending(b, w)) {
		/*
		 * There was a race, we'll just ignore this second
		 * bit of work for the same oblock.
		 */
		kmem_cache_free(b->work_cache, w);
		return -EINVAL;
	}

	if (pwork) {
		*pwork = &w->work;
		list_add(&w->list, &b->issued);
	} else
		list_add(&w->list, &b->queued);
	update_stats(b, &w->work, 1);

	return 0;
}