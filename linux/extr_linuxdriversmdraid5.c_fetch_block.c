#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stripe_head_state {int uptodate; int failed; int* failed_num; int req_compute; int syncing; int /*<<< orphan*/  locked; int /*<<< orphan*/  ops_request; } ;
struct TYPE_2__ {int target; int target2; } ;
struct stripe_head {int batch_head; scalar_t__ qd_idx; int pd_idx; TYPE_1__ ops; struct r5dev* dev; int /*<<< orphan*/  state; scalar_t__ sector; } ;
struct r5dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  R5_Insync ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  R5_Wantcompute ; 
 int /*<<< orphan*/  R5_Wantread ; 
 int /*<<< orphan*/  STRIPE_COMPUTE_RUN ; 
 int /*<<< orphan*/  STRIPE_OP_COMPUTE_BLK ; 
 scalar_t__ need_this_block (struct stripe_head*,struct stripe_head_state*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fetch_block(struct stripe_head *sh, struct stripe_head_state *s,
		       int disk_idx, int disks)
{
	struct r5dev *dev = &sh->dev[disk_idx];

	/* is the data in this block needed, and can we get it? */
	if (need_this_block(sh, s, disk_idx, disks)) {
		/* we would like to get this block, possibly by computing it,
		 * otherwise read it if the backing disk is insync
		 */
		BUG_ON(test_bit(R5_Wantcompute, &dev->flags));
		BUG_ON(test_bit(R5_Wantread, &dev->flags));
		BUG_ON(sh->batch_head);

		/*
		 * In the raid6 case if the only non-uptodate disk is P
		 * then we already trusted P to compute the other failed
		 * drives. It is safe to compute rather than re-read P.
		 * In other cases we only compute blocks from failed
		 * devices, otherwise check/repair might fail to detect
		 * a real inconsistency.
		 */

		if ((s->uptodate == disks - 1) &&
		    ((sh->qd_idx >= 0 && sh->pd_idx == disk_idx) ||
		    (s->failed && (disk_idx == s->failed_num[0] ||
				   disk_idx == s->failed_num[1])))) {
			/* have disk failed, and we're requested to fetch it;
			 * do compute it
			 */
			pr_debug("Computing stripe %llu block %d\n",
			       (unsigned long long)sh->sector, disk_idx);
			set_bit(STRIPE_COMPUTE_RUN, &sh->state);
			set_bit(STRIPE_OP_COMPUTE_BLK, &s->ops_request);
			set_bit(R5_Wantcompute, &dev->flags);
			sh->ops.target = disk_idx;
			sh->ops.target2 = -1; /* no 2nd target */
			s->req_compute = 1;
			/* Careful: from this point on 'uptodate' is in the eye
			 * of raid_run_ops which services 'compute' operations
			 * before writes. R5_Wantcompute flags a block that will
			 * be R5_UPTODATE by the time it is needed for a
			 * subsequent operation.
			 */
			s->uptodate++;
			return 1;
		} else if (s->uptodate == disks-2 && s->failed >= 2) {
			/* Computing 2-failure is *very* expensive; only
			 * do it if failed >= 2
			 */
			int other;
			for (other = disks; other--; ) {
				if (other == disk_idx)
					continue;
				if (!test_bit(R5_UPTODATE,
				      &sh->dev[other].flags))
					break;
			}
			BUG_ON(other < 0);
			pr_debug("Computing stripe %llu blocks %d,%d\n",
			       (unsigned long long)sh->sector,
			       disk_idx, other);
			set_bit(STRIPE_COMPUTE_RUN, &sh->state);
			set_bit(STRIPE_OP_COMPUTE_BLK, &s->ops_request);
			set_bit(R5_Wantcompute, &sh->dev[disk_idx].flags);
			set_bit(R5_Wantcompute, &sh->dev[other].flags);
			sh->ops.target = disk_idx;
			sh->ops.target2 = other;
			s->uptodate += 2;
			s->req_compute = 1;
			return 1;
		} else if (test_bit(R5_Insync, &dev->flags)) {
			set_bit(R5_LOCKED, &dev->flags);
			set_bit(R5_Wantread, &dev->flags);
			s->locked++;
			pr_debug("Reading block %d (sync=%d)\n",
				disk_idx, s->syncing);
		}
	}

	return 0;
}