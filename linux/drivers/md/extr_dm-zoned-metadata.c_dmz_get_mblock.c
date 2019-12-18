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
struct dmz_metadata {int /*<<< orphan*/  mblk_lock; } ;
struct dmz_mblock {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_META_ERROR ; 
 int /*<<< orphan*/  DMZ_META_READING ; 
 int /*<<< orphan*/  EIO ; 
 struct dmz_mblock* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dmz_mblock*) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct dmz_mblock* dmz_get_mblock_fast (struct dmz_metadata*,int /*<<< orphan*/ ) ; 
 struct dmz_mblock* dmz_get_mblock_slow (struct dmz_metadata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_release_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dmz_mblock *dmz_get_mblock(struct dmz_metadata *zmd,
					 sector_t mblk_no)
{
	struct dmz_mblock *mblk;

	/* Check rbtree */
	spin_lock(&zmd->mblk_lock);
	mblk = dmz_get_mblock_fast(zmd, mblk_no);
	spin_unlock(&zmd->mblk_lock);

	if (!mblk) {
		/* Cache miss: read the block from disk */
		mblk = dmz_get_mblock_slow(zmd, mblk_no);
		if (IS_ERR(mblk))
			return mblk;
	}

	/* Wait for on-going read I/O and check for error */
	wait_on_bit_io(&mblk->state, DMZ_META_READING,
		       TASK_UNINTERRUPTIBLE);
	if (test_bit(DMZ_META_ERROR, &mblk->state)) {
		dmz_release_mblock(zmd, mblk);
		return ERR_PTR(-EIO);
	}

	return mblk;
}