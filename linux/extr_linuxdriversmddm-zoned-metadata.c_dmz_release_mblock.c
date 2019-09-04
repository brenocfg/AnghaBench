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
struct dmz_metadata {int /*<<< orphan*/  mblk_lock; int /*<<< orphan*/  mblk_lru_list; int /*<<< orphan*/  mblk_rbtree; } ;
struct dmz_mblock {scalar_t__ ref; int /*<<< orphan*/  link; int /*<<< orphan*/  state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_META_DIRTY ; 
 int /*<<< orphan*/  DMZ_META_ERROR ; 
 int /*<<< orphan*/  dmz_free_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 int /*<<< orphan*/  dmz_shrink_mblock_cache (struct dmz_metadata*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmz_release_mblock(struct dmz_metadata *zmd,
			       struct dmz_mblock *mblk)
{

	if (!mblk)
		return;

	spin_lock(&zmd->mblk_lock);

	mblk->ref--;
	if (mblk->ref == 0) {
		if (test_bit(DMZ_META_ERROR, &mblk->state)) {
			rb_erase(&mblk->node, &zmd->mblk_rbtree);
			dmz_free_mblock(zmd, mblk);
		} else if (!test_bit(DMZ_META_DIRTY, &mblk->state)) {
			list_add_tail(&mblk->link, &zmd->mblk_lru_list);
			dmz_shrink_mblock_cache(zmd, 1);
		}
	}

	spin_unlock(&zmd->mblk_lock);
}