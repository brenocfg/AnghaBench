#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {int disks; int qd_idx; int pd_idx; TYPE_2__* dev; int /*<<< orphan*/  sector; } ;
struct r5l_recovery_ctx {int /*<<< orphan*/  data_parity_stripes; } ;
struct r5conf {TYPE_1__* disks; } ;
struct md_rdev {int /*<<< orphan*/  mddev; int /*<<< orphan*/  nr_pending; } ;
struct TYPE_4__ {int /*<<< orphan*/  page; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  replacement; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  R5_Wantwrite ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5l_recovery_reset_stripe (struct stripe_head*) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_page_io (struct md_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
r5l_recovery_replay_one_stripe(struct r5conf *conf,
			       struct stripe_head *sh,
			       struct r5l_recovery_ctx *ctx)
{
	struct md_rdev *rdev, *rrdev;
	int disk_index;
	int data_count = 0;

	for (disk_index = 0; disk_index < sh->disks; disk_index++) {
		if (!test_bit(R5_Wantwrite, &sh->dev[disk_index].flags))
			continue;
		if (disk_index == sh->qd_idx || disk_index == sh->pd_idx)
			continue;
		data_count++;
	}

	/*
	 * stripes that only have parity must have been flushed
	 * before the crash that we are now recovering from, so
	 * there is nothing more to recovery.
	 */
	if (data_count == 0)
		goto out;

	for (disk_index = 0; disk_index < sh->disks; disk_index++) {
		if (!test_bit(R5_Wantwrite, &sh->dev[disk_index].flags))
			continue;

		/* in case device is broken */
		rcu_read_lock();
		rdev = rcu_dereference(conf->disks[disk_index].rdev);
		if (rdev) {
			atomic_inc(&rdev->nr_pending);
			rcu_read_unlock();
			sync_page_io(rdev, sh->sector, PAGE_SIZE,
				     sh->dev[disk_index].page, REQ_OP_WRITE, 0,
				     false);
			rdev_dec_pending(rdev, rdev->mddev);
			rcu_read_lock();
		}
		rrdev = rcu_dereference(conf->disks[disk_index].replacement);
		if (rrdev) {
			atomic_inc(&rrdev->nr_pending);
			rcu_read_unlock();
			sync_page_io(rrdev, sh->sector, PAGE_SIZE,
				     sh->dev[disk_index].page, REQ_OP_WRITE, 0,
				     false);
			rdev_dec_pending(rrdev, rrdev->mddev);
			rcu_read_lock();
		}
		rcu_read_unlock();
	}
	ctx->data_parity_stripes++;
out:
	r5l_recovery_reset_stripe(sh);
}