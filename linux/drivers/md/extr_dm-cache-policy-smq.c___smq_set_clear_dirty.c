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
struct smq_policy {int /*<<< orphan*/  cache_alloc; } ;
struct entry {int dirty; scalar_t__ pending_work; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_queue (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 struct entry* get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_queue (struct smq_policy*,struct entry*) ; 

__attribute__((used)) static void __smq_set_clear_dirty(struct smq_policy *mq, dm_cblock_t cblock, bool set)
{
	struct entry *e = get_entry(&mq->cache_alloc, from_cblock(cblock));

	if (e->pending_work)
		e->dirty = set;
	else {
		del_queue(mq, e);
		e->dirty = set;
		push_queue(mq, e);
	}
}