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
struct stripe_head_state {size_t* failed_num; int failed; int /*<<< orphan*/  to_write; scalar_t__ replacing; scalar_t__ expanding; scalar_t__ syncing; } ;
struct stripe_head {scalar_t__ sector; scalar_t__ pd_idx; scalar_t__ qd_idx; TYPE_2__* raid_conf; int /*<<< orphan*/  state; struct r5dev* dev; } ;
struct r5dev {int /*<<< orphan*/  flags; scalar_t__ towrite; scalar_t__ toread; } ;
struct TYPE_4__ {int level; TYPE_1__* mddev; } ;
struct TYPE_3__ {scalar_t__ recovery_cp; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_Insync ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_OVERWRITE ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ want_replace (struct stripe_head*,int) ; 

__attribute__((used)) static int need_this_block(struct stripe_head *sh, struct stripe_head_state *s,
			   int disk_idx, int disks)
{
	struct r5dev *dev = &sh->dev[disk_idx];
	struct r5dev *fdev[2] = { &sh->dev[s->failed_num[0]],
				  &sh->dev[s->failed_num[1]] };
	int i;


	if (test_bit(R5_LOCKED, &dev->flags) ||
	    test_bit(R5_UPTODATE, &dev->flags))
		/* No point reading this as we already have it or have
		 * decided to get it.
		 */
		return 0;

	if (dev->toread ||
	    (dev->towrite && !test_bit(R5_OVERWRITE, &dev->flags)))
		/* We need this block to directly satisfy a request */
		return 1;

	if (s->syncing || s->expanding ||
	    (s->replacing && want_replace(sh, disk_idx)))
		/* When syncing, or expanding we read everything.
		 * When replacing, we need the replaced block.
		 */
		return 1;

	if ((s->failed >= 1 && fdev[0]->toread) ||
	    (s->failed >= 2 && fdev[1]->toread))
		/* If we want to read from a failed device, then
		 * we need to actually read every other device.
		 */
		return 1;

	/* Sometimes neither read-modify-write nor reconstruct-write
	 * cycles can work.  In those cases we read every block we
	 * can.  Then the parity-update is certain to have enough to
	 * work with.
	 * This can only be a problem when we need to write something,
	 * and some device has failed.  If either of those tests
	 * fail we need look no further.
	 */
	if (!s->failed || !s->to_write)
		return 0;

	if (test_bit(R5_Insync, &dev->flags) &&
	    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		/* Pre-reads at not permitted until after short delay
		 * to gather multiple requests.  However if this
		 * device is no Insync, the block could only be computed
		 * and there is no need to delay that.
		 */
		return 0;

	for (i = 0; i < s->failed && i < 2; i++) {
		if (fdev[i]->towrite &&
		    !test_bit(R5_UPTODATE, &fdev[i]->flags) &&
		    !test_bit(R5_OVERWRITE, &fdev[i]->flags))
			/* If we have a partial write to a failed
			 * device, then we will need to reconstruct
			 * the content of that device, so all other
			 * devices must be read.
			 */
			return 1;
	}

	/* If we are forced to do a reconstruct-write, either because
	 * the current RAID6 implementation only supports that, or
	 * because parity cannot be trusted and we are currently
	 * recovering it, there is extra need to be careful.
	 * If one of the devices that we would need to read, because
	 * it is not being overwritten (and maybe not written at all)
	 * is missing/faulty, then we need to read everything we can.
	 */
	if (sh->raid_conf->level != 6 &&
	    sh->sector < sh->raid_conf->mddev->recovery_cp)
		/* reconstruct-write isn't being forced */
		return 0;
	for (i = 0; i < s->failed && i < 2; i++) {
		if (s->failed_num[i] != sh->pd_idx &&
		    s->failed_num[i] != sh->qd_idx &&
		    !test_bit(R5_UPTODATE, &fdev[i]->flags) &&
		    !test_bit(R5_OVERWRITE, &fdev[i]->flags))
			return 1;
	}

	return 0;
}