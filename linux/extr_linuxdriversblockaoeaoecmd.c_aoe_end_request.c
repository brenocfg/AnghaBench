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
struct request_queue {int dummy; } ;
struct request {struct bio* bio; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_size; } ;
struct bio {int /*<<< orphan*/  bi_status; TYPE_2__ bi_iter; } ;
struct TYPE_3__ {struct request* rq; } ;
struct aoedev {TYPE_1__ ip; struct request_queue* blkq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ __blk_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 

void
aoe_end_request(struct aoedev *d, struct request *rq, int fastfail)
{
	struct bio *bio;
	int bok;
	struct request_queue *q;

	q = d->blkq;
	if (rq == d->ip.rq)
		d->ip.rq = NULL;
	do {
		bio = rq->bio;
		bok = !fastfail && !bio->bi_status;
	} while (__blk_end_request(rq, bok ? BLK_STS_OK : BLK_STS_IOERR, bio->bi_iter.bi_size));

	/* cf. http://lkml.org/lkml/2006/10/31/28 */
	if (!fastfail)
		__blk_run_queue(q);
}