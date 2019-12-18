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
struct mddev {int /*<<< orphan*/  bio_set; struct faulty_conf* private; } ;
struct faulty_conf {TYPE_2__* rdev; int /*<<< orphan*/ * counters; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct bio* bi_private; TYPE_1__ bi_iter; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  ReadFixable ; 
 int /*<<< orphan*/  ReadPersistent ; 
 int /*<<< orphan*/  ReadTransient ; 
 scalar_t__ WRITE ; 
 size_t WriteAll ; 
 int /*<<< orphan*/  WritePersistent ; 
 int /*<<< orphan*/  WriteTransient ; 
 int /*<<< orphan*/  add_sector (struct faulty_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_mode (struct faulty_conf*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_sector (struct faulty_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  faulty_fail ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static bool faulty_make_request(struct mddev *mddev, struct bio *bio)
{
	struct faulty_conf *conf = mddev->private;
	int failit = 0;

	if (bio_data_dir(bio) == WRITE) {
		/* write request */
		if (atomic_read(&conf->counters[WriteAll])) {
			/* special case - don't decrement, don't generic_make_request,
			 * just fail immediately
			 */
			bio_io_error(bio);
			return true;
		}

		if (check_sector(conf, bio->bi_iter.bi_sector,
				 bio_end_sector(bio), WRITE))
			failit = 1;
		if (check_mode(conf, WritePersistent)) {
			add_sector(conf, bio->bi_iter.bi_sector,
				   WritePersistent);
			failit = 1;
		}
		if (check_mode(conf, WriteTransient))
			failit = 1;
	} else {
		/* read request */
		if (check_sector(conf, bio->bi_iter.bi_sector,
				 bio_end_sector(bio), READ))
			failit = 1;
		if (check_mode(conf, ReadTransient))
			failit = 1;
		if (check_mode(conf, ReadPersistent)) {
			add_sector(conf, bio->bi_iter.bi_sector,
				   ReadPersistent);
			failit = 1;
		}
		if (check_mode(conf, ReadFixable)) {
			add_sector(conf, bio->bi_iter.bi_sector,
				   ReadFixable);
			failit = 1;
		}
	}
	if (failit) {
		struct bio *b = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);

		bio_set_dev(b, conf->rdev->bdev);
		b->bi_private = bio;
		b->bi_end_io = faulty_fail;
		bio = b;
	} else
		bio_set_dev(bio, conf->rdev->bdev);

	generic_make_request(bio);
	return true;
}