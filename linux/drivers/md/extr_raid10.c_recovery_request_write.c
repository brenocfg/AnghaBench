#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r10conf {TYPE_4__* mirrors; } ;
struct r10bio {TYPE_1__* devs; int /*<<< orphan*/  state; } ;
struct mddev {struct r10conf* private; } ;
struct bio {scalar_t__ bi_end_io; } ;
struct TYPE_8__ {TYPE_3__* replacement; TYPE_2__* rdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  bdev; int /*<<< orphan*/  nr_pending; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; int /*<<< orphan*/  nr_pending; } ;
struct TYPE_5__ {int devnum; struct bio* repl_bio; struct bio* bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  R10BIO_Uptodate ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  end_sync_request (struct r10bio*) ; 
 int /*<<< orphan*/  fix_recovery_read_error (struct r10bio*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  md_sync_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recovery_request_write(struct mddev *mddev, struct r10bio *r10_bio)
{
	struct r10conf *conf = mddev->private;
	int d;
	struct bio *wbio, *wbio2;

	if (!test_bit(R10BIO_Uptodate, &r10_bio->state)) {
		fix_recovery_read_error(r10_bio);
		end_sync_request(r10_bio);
		return;
	}

	/*
	 * share the pages with the first bio
	 * and submit the write request
	 */
	d = r10_bio->devs[1].devnum;
	wbio = r10_bio->devs[1].bio;
	wbio2 = r10_bio->devs[1].repl_bio;
	/* Need to test wbio2->bi_end_io before we call
	 * generic_make_request as if the former is NULL,
	 * the latter is free to free wbio2.
	 */
	if (wbio2 && !wbio2->bi_end_io)
		wbio2 = NULL;
	if (wbio->bi_end_io) {
		atomic_inc(&conf->mirrors[d].rdev->nr_pending);
		md_sync_acct(conf->mirrors[d].rdev->bdev, bio_sectors(wbio));
		generic_make_request(wbio);
	}
	if (wbio2) {
		atomic_inc(&conf->mirrors[d].replacement->nr_pending);
		md_sync_acct(conf->mirrors[d].replacement->bdev,
			     bio_sectors(wbio2));
		generic_make_request(wbio2);
	}
}