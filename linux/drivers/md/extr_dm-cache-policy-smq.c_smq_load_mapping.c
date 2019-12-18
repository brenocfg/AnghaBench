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
typedef  int /*<<< orphan*/  uint32_t ;
struct smq_policy {int /*<<< orphan*/  cache_alloc; } ;
struct entry {int dirty; int pending_work; int /*<<< orphan*/  level; int /*<<< orphan*/  oblock; } ;
struct dm_cache_policy {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 scalar_t__ NR_CACHE_LEVELS ; 
 struct entry* alloc_particular_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  push_front (struct smq_policy*,struct entry*) ; 
 int /*<<< orphan*/  random_level (int /*<<< orphan*/ ) ; 
 struct smq_policy* to_smq_policy (struct dm_cache_policy*) ; 

__attribute__((used)) static int smq_load_mapping(struct dm_cache_policy *p,
			    dm_oblock_t oblock, dm_cblock_t cblock,
			    bool dirty, uint32_t hint, bool hint_valid)
{
	struct smq_policy *mq = to_smq_policy(p);
	struct entry *e;

	e = alloc_particular_entry(&mq->cache_alloc, from_cblock(cblock));
	e->oblock = oblock;
	e->dirty = dirty;
	e->level = hint_valid ? min(hint, NR_CACHE_LEVELS - 1) : random_level(cblock);
	e->pending_work = false;

	/*
	 * When we load mappings we push ahead of both sentinels in order to
	 * allow demotions and cleaning to occur immediately.
	 */
	push_front(mq, e);

	return 0;
}