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
struct closure {int dummy; } ;
struct bio {struct cached_dev* bi_private; int /*<<< orphan*/  bi_end_io; } ;
struct cached_dev {int /*<<< orphan*/  sb; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sb_write_mutex; struct bio sb_bio; struct closure sb_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  __write_super (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bch_write_bdev_super_unlock ; 
 int /*<<< orphan*/  bio_reset (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closure_get (struct closure*) ; 
 int /*<<< orphan*/  closure_init (struct closure*,struct closure*) ; 
 int /*<<< orphan*/  closure_return_with_destructor (struct closure*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_bdev_super_endio ; 

void bch_write_bdev_super(struct cached_dev *dc, struct closure *parent)
{
	struct closure *cl = &dc->sb_write;
	struct bio *bio = &dc->sb_bio;

	down(&dc->sb_write_mutex);
	closure_init(cl, parent);

	bio_reset(bio);
	bio_set_dev(bio, dc->bdev);
	bio->bi_end_io	= write_bdev_super_endio;
	bio->bi_private = dc;

	closure_get(cl);
	/* I/O request sent to backing device */
	__write_super(&dc->sb, bio);

	closure_return_with_destructor(cl, bch_write_bdev_super_unlock);
}