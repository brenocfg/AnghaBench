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
struct smq_policy {int /*<<< orphan*/  cache_alloc; int /*<<< orphan*/  table; } ;
struct entry {int /*<<< orphan*/  allocated; } ;
struct dm_cache_policy {int dummy; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  del_queue (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  free_entry (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 struct entry* get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_remove (int /*<<< orphan*/ *,struct entry*) ; 
 struct smq_policy* to_smq_policy (struct dm_cache_policy*) ; 

__attribute__((used)) static int smq_invalidate_mapping(struct dm_cache_policy *p, dm_cblock_t cblock)
{
	struct smq_policy *mq = to_smq_policy(p);
	struct entry *e = get_entry(&mq->cache_alloc, from_cblock(cblock));

	if (!e->allocated)
		return -ENODATA;

	// FIXME: what if this block has pending background work?
	del_queue(mq, e);
	h_remove(&mq->table, e);
	free_entry(&mq->cache_alloc, e);
	return 0;
}