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
struct shadow_info {int /*<<< orphan*/  hlist; int /*<<< orphan*/  where; } ;
struct dm_transaction_manager {int /*<<< orphan*/  lock; scalar_t__ buckets; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_HASH_MASK ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 unsigned int dm_hash_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,scalar_t__) ; 
 struct shadow_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_shadow(struct dm_transaction_manager *tm, dm_block_t b)
{
	unsigned bucket;
	struct shadow_info *si;

	si = kmalloc(sizeof(*si), GFP_NOIO);
	if (si) {
		si->where = b;
		bucket = dm_hash_block(b, DM_HASH_MASK);
		spin_lock(&tm->lock);
		hlist_add_head(&si->hlist, tm->buckets + bucket);
		spin_unlock(&tm->lock);
	}
}