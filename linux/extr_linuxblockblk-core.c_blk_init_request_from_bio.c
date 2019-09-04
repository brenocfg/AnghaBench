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
struct request {int /*<<< orphan*/  q; int /*<<< orphan*/  write_hint; int /*<<< orphan*/  ioprio; int /*<<< orphan*/  __sector; int /*<<< orphan*/  cmd_flags; } ;
struct io_context {int /*<<< orphan*/  ioprio; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_write_hint; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPRIO_CLASS_NONE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_FAILFAST_MASK ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  bio_prio (struct bio*) ; 
 int /*<<< orphan*/  blk_rq_bio_prep (int /*<<< orphan*/ ,struct request*,struct bio*) ; 
 scalar_t__ ioprio_valid (int /*<<< orphan*/ ) ; 
 struct io_context* rq_ioc (struct bio*) ; 

void blk_init_request_from_bio(struct request *req, struct bio *bio)
{
	struct io_context *ioc = rq_ioc(bio);

	if (bio->bi_opf & REQ_RAHEAD)
		req->cmd_flags |= REQ_FAILFAST_MASK;

	req->__sector = bio->bi_iter.bi_sector;
	if (ioprio_valid(bio_prio(bio)))
		req->ioprio = bio_prio(bio);
	else if (ioc)
		req->ioprio = ioc->ioprio;
	else
		req->ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_NONE, 0);
	req->write_hint = bio->bi_write_hint;
	blk_rq_bio_prep(req->q, req, bio);
}