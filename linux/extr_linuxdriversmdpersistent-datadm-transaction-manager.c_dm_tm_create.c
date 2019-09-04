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
struct dm_transaction_manager {int /*<<< orphan*/  prefetches; scalar_t__ buckets; int /*<<< orphan*/  lock; struct dm_space_map* sm; struct dm_block_manager* bm; int /*<<< orphan*/ * real; scalar_t__ is_clone; } ;
struct dm_space_map {int dummy; } ;
struct dm_block_manager {int dummy; } ;

/* Variables and functions */
 int DM_HASH_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dm_transaction_manager* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (scalar_t__) ; 
 struct dm_transaction_manager* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dm_transaction_manager *dm_tm_create(struct dm_block_manager *bm,
						   struct dm_space_map *sm)
{
	int i;
	struct dm_transaction_manager *tm;

	tm = kmalloc(sizeof(*tm), GFP_KERNEL);
	if (!tm)
		return ERR_PTR(-ENOMEM);

	tm->is_clone = 0;
	tm->real = NULL;
	tm->bm = bm;
	tm->sm = sm;

	spin_lock_init(&tm->lock);
	for (i = 0; i < DM_HASH_SIZE; i++)
		INIT_HLIST_HEAD(tm->buckets + i);

	prefetch_init(&tm->prefetches);

	return tm;
}