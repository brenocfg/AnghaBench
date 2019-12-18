#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {int disks; scalar_t__ qd_idx; int pd_idx; int /*<<< orphan*/  state; TYPE_2__* dev; scalar_t__ sector; int /*<<< orphan*/  count; struct r5conf* raid_conf; } ;
struct r5conf {scalar_t__ max_degraded; scalar_t__ max_nr_stripes; TYPE_3__* mddev; TYPE_1__* disks; } ;
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  read_errors; int /*<<< orphan*/  bdev; int /*<<< orphan*/  corrected_errors; scalar_t__ data_offset; scalar_t__ new_data_offset; } ;
struct bio {scalar_t__ bi_status; struct stripe_head* bi_private; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_8__ {scalar_t__ degraded; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; struct bio req; } ;
struct TYPE_6__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 scalar_t__ BLK_STS_PROTECTION ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_OrigPageUPTDODATE ; 
 int /*<<< orphan*/  R5_ReWrite ; 
 int /*<<< orphan*/  R5_ReadError ; 
 int /*<<< orphan*/  R5_ReadNoMerge ; 
 int /*<<< orphan*/  R5_ReadRepl ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_SECTORS ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bio_reset (struct bio*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_error (TYPE_3__*,struct md_rdev*) ; 
 int /*<<< orphan*/  mdname (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,unsigned long long,char const*) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,TYPE_3__*) ; 
 scalar_t__ rdev_set_badblocks (struct md_rdev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ use_new_offset (struct r5conf*,struct stripe_head*) ; 

__attribute__((used)) static void raid5_end_read_request(struct bio * bi)
{
	struct stripe_head *sh = bi->bi_private;
	struct r5conf *conf = sh->raid_conf;
	int disks = sh->disks, i;
	char b[BDEVNAME_SIZE];
	struct md_rdev *rdev = NULL;
	sector_t s;

	for (i=0 ; i<disks; i++)
		if (bi == &sh->dev[i].req)
			break;

	pr_debug("end_read_request %llu/%d, count: %d, error %d.\n",
		(unsigned long long)sh->sector, i, atomic_read(&sh->count),
		bi->bi_status);
	if (i == disks) {
		bio_reset(bi);
		BUG();
		return;
	}
	if (test_bit(R5_ReadRepl, &sh->dev[i].flags))
		/* If replacement finished while this request was outstanding,
		 * 'replacement' might be NULL already.
		 * In that case it moved down to 'rdev'.
		 * rdev is not removed until all requests are finished.
		 */
		rdev = conf->disks[i].replacement;
	if (!rdev)
		rdev = conf->disks[i].rdev;

	if (use_new_offset(conf, sh))
		s = sh->sector + rdev->new_data_offset;
	else
		s = sh->sector + rdev->data_offset;
	if (!bi->bi_status) {
		set_bit(R5_UPTODATE, &sh->dev[i].flags);
		if (test_bit(R5_ReadError, &sh->dev[i].flags)) {
			/* Note that this cannot happen on a
			 * replacement device.  We just fail those on
			 * any error
			 */
			pr_info_ratelimited(
				"md/raid:%s: read error corrected (%lu sectors at %llu on %s)\n",
				mdname(conf->mddev), STRIPE_SECTORS,
				(unsigned long long)s,
				bdevname(rdev->bdev, b));
			atomic_add(STRIPE_SECTORS, &rdev->corrected_errors);
			clear_bit(R5_ReadError, &sh->dev[i].flags);
			clear_bit(R5_ReWrite, &sh->dev[i].flags);
		} else if (test_bit(R5_ReadNoMerge, &sh->dev[i].flags))
			clear_bit(R5_ReadNoMerge, &sh->dev[i].flags);

		if (test_bit(R5_InJournal, &sh->dev[i].flags))
			/*
			 * end read for a page in journal, this
			 * must be preparing for prexor in rmw
			 */
			set_bit(R5_OrigPageUPTDODATE, &sh->dev[i].flags);

		if (atomic_read(&rdev->read_errors))
			atomic_set(&rdev->read_errors, 0);
	} else {
		const char *bdn = bdevname(rdev->bdev, b);
		int retry = 0;
		int set_bad = 0;

		clear_bit(R5_UPTODATE, &sh->dev[i].flags);
		if (!(bi->bi_status == BLK_STS_PROTECTION))
			atomic_inc(&rdev->read_errors);
		if (test_bit(R5_ReadRepl, &sh->dev[i].flags))
			pr_warn_ratelimited(
				"md/raid:%s: read error on replacement device (sector %llu on %s).\n",
				mdname(conf->mddev),
				(unsigned long long)s,
				bdn);
		else if (conf->mddev->degraded >= conf->max_degraded) {
			set_bad = 1;
			pr_warn_ratelimited(
				"md/raid:%s: read error not correctable (sector %llu on %s).\n",
				mdname(conf->mddev),
				(unsigned long long)s,
				bdn);
		} else if (test_bit(R5_ReWrite, &sh->dev[i].flags)) {
			/* Oh, no!!! */
			set_bad = 1;
			pr_warn_ratelimited(
				"md/raid:%s: read error NOT corrected!! (sector %llu on %s).\n",
				mdname(conf->mddev),
				(unsigned long long)s,
				bdn);
		} else if (atomic_read(&rdev->read_errors)
			 > conf->max_nr_stripes) {
			if (!test_bit(Faulty, &rdev->flags)) {
				pr_warn("md/raid:%s: %d read_errors > %d stripes\n",
				    mdname(conf->mddev),
				    atomic_read(&rdev->read_errors),
				    conf->max_nr_stripes);
				pr_warn("md/raid:%s: Too many read errors, failing device %s.\n",
				    mdname(conf->mddev), bdn);
			}
		} else
			retry = 1;
		if (set_bad && test_bit(In_sync, &rdev->flags)
		    && !test_bit(R5_ReadNoMerge, &sh->dev[i].flags))
			retry = 1;
		if (retry)
			if (sh->qd_idx >= 0 && sh->pd_idx == i)
				set_bit(R5_ReadError, &sh->dev[i].flags);
			else if (test_bit(R5_ReadNoMerge, &sh->dev[i].flags)) {
				set_bit(R5_ReadError, &sh->dev[i].flags);
				clear_bit(R5_ReadNoMerge, &sh->dev[i].flags);
			} else
				set_bit(R5_ReadNoMerge, &sh->dev[i].flags);
		else {
			clear_bit(R5_ReadError, &sh->dev[i].flags);
			clear_bit(R5_ReWrite, &sh->dev[i].flags);
			if (!(set_bad
			      && test_bit(In_sync, &rdev->flags)
			      && rdev_set_badblocks(
				      rdev, sh->sector, STRIPE_SECTORS, 0)))
				md_error(conf->mddev, rdev);
		}
	}
	rdev_dec_pending(rdev, conf->mddev);
	bio_reset(bi);
	clear_bit(R5_LOCKED, &sh->dev[i].flags);
	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
}