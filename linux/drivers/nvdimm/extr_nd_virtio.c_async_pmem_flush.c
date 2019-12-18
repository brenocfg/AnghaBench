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
struct nd_region {int dummy; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_copy_dev (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 scalar_t__ virtio_pmem_flush (struct nd_region*) ; 

int async_pmem_flush(struct nd_region *nd_region, struct bio *bio)
{
	/*
	 * Create child bio for asynchronous flush and chain with
	 * parent bio. Otherwise directly call nd_region flush.
	 */
	if (bio && bio->bi_iter.bi_sector != -1) {
		struct bio *child = bio_alloc(GFP_ATOMIC, 0);

		if (!child)
			return -ENOMEM;
		bio_copy_dev(child, bio);
		child->bi_opf = REQ_PREFLUSH;
		child->bi_iter.bi_sector = -1;
		bio_chain(child, bio);
		submit_bio(child);
		return 0;
	}
	if (virtio_pmem_flush(nd_region))
		return -EIO;

	return 0;
}