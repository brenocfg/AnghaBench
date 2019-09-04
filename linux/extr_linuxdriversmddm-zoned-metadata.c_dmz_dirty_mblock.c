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
struct dmz_metadata {int /*<<< orphan*/  mblk_lock; int /*<<< orphan*/  mblk_dirty_list; } ;
struct dmz_mblock {int /*<<< orphan*/  link; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_META_DIRTY ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmz_dirty_mblock(struct dmz_metadata *zmd, struct dmz_mblock *mblk)
{
	spin_lock(&zmd->mblk_lock);
	if (!test_and_set_bit(DMZ_META_DIRTY, &mblk->state))
		list_add_tail(&mblk->link, &zmd->mblk_dirty_list);
	spin_unlock(&zmd->mblk_lock);
}