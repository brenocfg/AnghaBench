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
struct r5l_log {scalar_t__ log_start; TYPE_2__* rdev; int /*<<< orphan*/  bs; } ;
struct TYPE_3__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
struct TYPE_4__ {scalar_t__ data_offset; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio *r5l_bio_alloc(struct r5l_log *log)
{
	struct bio *bio = bio_alloc_bioset(GFP_NOIO, BIO_MAX_PAGES, &log->bs);

	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
	bio_set_dev(bio, log->rdev->bdev);
	bio->bi_iter.bi_sector = log->rdev->data_offset + log->log_start;

	return bio;
}