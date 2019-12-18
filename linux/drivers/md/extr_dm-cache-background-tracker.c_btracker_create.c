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
struct background_tracker {unsigned int max_work; int /*<<< orphan*/  work_cache; int /*<<< orphan*/  pending; int /*<<< orphan*/  queued; int /*<<< orphan*/  issued; int /*<<< orphan*/  pending_demotes; int /*<<< orphan*/  pending_writebacks; int /*<<< orphan*/  pending_promotes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KMEM_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_work ; 
 int /*<<< orphan*/  kfree (struct background_tracker*) ; 
 struct background_tracker* kmalloc (int,int /*<<< orphan*/ ) ; 

struct background_tracker *btracker_create(unsigned max_work)
{
	struct background_tracker *b = kmalloc(sizeof(*b), GFP_KERNEL);

	if (!b) {
		DMERR("couldn't create background_tracker");
		return NULL;
	}

	b->max_work = max_work;
	atomic_set(&b->pending_promotes, 0);
	atomic_set(&b->pending_writebacks, 0);
	atomic_set(&b->pending_demotes, 0);

	INIT_LIST_HEAD(&b->issued);
	INIT_LIST_HEAD(&b->queued);

	b->pending = RB_ROOT;
	b->work_cache = KMEM_CACHE(bt_work, 0);
	if (!b->work_cache) {
		DMERR("couldn't create mempool for background work items");
		kfree(b);
		b = NULL;
	}

	return b;
}