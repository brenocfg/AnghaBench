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
struct resync_pages {struct r10bio* raid_bio; struct page** pages; } ;
struct r10conf {int copies; TYPE_3__* mirrors; } ;
struct r10bio {int sectors; int /*<<< orphan*/  remaining; TYPE_4__* devs; } ;
struct page {int dummy; } ;
struct mddev {int /*<<< orphan*/  recovery; int /*<<< orphan*/  resync_mismatches; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; scalar_t__ data_offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  mddev; } ;
struct TYPE_6__ {int bi_size; int /*<<< orphan*/  bi_sector; scalar_t__ bi_idx; } ;
struct bio {scalar_t__ bi_end_io; TYPE_2__ bi_iter; int /*<<< orphan*/  bi_opf; struct resync_pages* bi_private; int /*<<< orphan*/  bi_status; } ;
struct TYPE_8__ {int devnum; struct bio* bio; struct bio* repl_bio; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {TYPE_1__* replacement; struct md_rdev* rdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FailFast ; 
 int /*<<< orphan*/  MD_FAILFAST ; 
 int /*<<< orphan*/  MD_RECOVERY_CHECK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_copy_data (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_reset (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ end_sync_read ; 
 scalar_t__ end_sync_write ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 struct resync_pages* get_resync_pages (struct bio*) ; 
 int /*<<< orphan*/  md_bio_reset_resync_pages (struct bio*,struct resync_pages*,int) ; 
 int /*<<< orphan*/  md_done_sync (struct mddev*,int,int) ; 
 int /*<<< orphan*/  md_error (int /*<<< orphan*/ ,struct md_rdev*) ; 
 int /*<<< orphan*/  md_sync_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_buf (struct r10bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sync_request_write(struct mddev *mddev, struct r10bio *r10_bio)
{
	struct r10conf *conf = mddev->private;
	int i, first;
	struct bio *tbio, *fbio;
	int vcnt;
	struct page **tpages, **fpages;

	atomic_set(&r10_bio->remaining, 1);

	/* find the first device with a block */
	for (i=0; i<conf->copies; i++)
		if (!r10_bio->devs[i].bio->bi_status)
			break;

	if (i == conf->copies)
		goto done;

	first = i;
	fbio = r10_bio->devs[i].bio;
	fbio->bi_iter.bi_size = r10_bio->sectors << 9;
	fbio->bi_iter.bi_idx = 0;
	fpages = get_resync_pages(fbio)->pages;

	vcnt = (r10_bio->sectors + (PAGE_SIZE >> 9) - 1) >> (PAGE_SHIFT - 9);
	/* now find blocks with errors */
	for (i=0 ; i < conf->copies ; i++) {
		int  j, d;
		struct md_rdev *rdev;
		struct resync_pages *rp;

		tbio = r10_bio->devs[i].bio;

		if (tbio->bi_end_io != end_sync_read)
			continue;
		if (i == first)
			continue;

		tpages = get_resync_pages(tbio)->pages;
		d = r10_bio->devs[i].devnum;
		rdev = conf->mirrors[d].rdev;
		if (!r10_bio->devs[i].bio->bi_status) {
			/* We know that the bi_io_vec layout is the same for
			 * both 'first' and 'i', so we just compare them.
			 * All vec entries are PAGE_SIZE;
			 */
			int sectors = r10_bio->sectors;
			for (j = 0; j < vcnt; j++) {
				int len = PAGE_SIZE;
				if (sectors < (len / 512))
					len = sectors * 512;
				if (memcmp(page_address(fpages[j]),
					   page_address(tpages[j]),
					   len))
					break;
				sectors -= len/512;
			}
			if (j == vcnt)
				continue;
			atomic64_add(r10_bio->sectors, &mddev->resync_mismatches);
			if (test_bit(MD_RECOVERY_CHECK, &mddev->recovery))
				/* Don't fix anything. */
				continue;
		} else if (test_bit(FailFast, &rdev->flags)) {
			/* Just give up on this device */
			md_error(rdev->mddev, rdev);
			continue;
		}
		/* Ok, we need to write this bio, either to correct an
		 * inconsistency or to correct an unreadable block.
		 * First we need to fixup bv_offset, bv_len and
		 * bi_vecs, as the read request might have corrupted these
		 */
		rp = get_resync_pages(tbio);
		bio_reset(tbio);

		md_bio_reset_resync_pages(tbio, rp, fbio->bi_iter.bi_size);

		rp->raid_bio = r10_bio;
		tbio->bi_private = rp;
		tbio->bi_iter.bi_sector = r10_bio->devs[i].addr;
		tbio->bi_end_io = end_sync_write;
		bio_set_op_attrs(tbio, REQ_OP_WRITE, 0);

		bio_copy_data(tbio, fbio);

		atomic_inc(&conf->mirrors[d].rdev->nr_pending);
		atomic_inc(&r10_bio->remaining);
		md_sync_acct(conf->mirrors[d].rdev->bdev, bio_sectors(tbio));

		if (test_bit(FailFast, &conf->mirrors[d].rdev->flags))
			tbio->bi_opf |= MD_FAILFAST;
		tbio->bi_iter.bi_sector += conf->mirrors[d].rdev->data_offset;
		bio_set_dev(tbio, conf->mirrors[d].rdev->bdev);
		generic_make_request(tbio);
	}

	/* Now write out to any replacement devices
	 * that are active
	 */
	for (i = 0; i < conf->copies; i++) {
		int d;

		tbio = r10_bio->devs[i].repl_bio;
		if (!tbio || !tbio->bi_end_io)
			continue;
		if (r10_bio->devs[i].bio->bi_end_io != end_sync_write
		    && r10_bio->devs[i].bio != fbio)
			bio_copy_data(tbio, fbio);
		d = r10_bio->devs[i].devnum;
		atomic_inc(&r10_bio->remaining);
		md_sync_acct(conf->mirrors[d].replacement->bdev,
			     bio_sectors(tbio));
		generic_make_request(tbio);
	}

done:
	if (atomic_dec_and_test(&r10_bio->remaining)) {
		md_done_sync(mddev, r10_bio->sectors, 1);
		put_buf(r10_bio);
	}
}