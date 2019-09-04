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
struct request {int dummy; } ;
struct bfq_queue {int seek_history; int /*<<< orphan*/  last_request_pos; } ;
struct bfq_data {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 scalar_t__ BFQQ_SECT_THR_NONROT ; 
 scalar_t__ BFQQ_SEEK_THR ; 
 int /*<<< orphan*/  blk_queue_nonrot (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 scalar_t__ get_sdist (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void
bfq_update_io_seektime(struct bfq_data *bfqd, struct bfq_queue *bfqq,
		       struct request *rq)
{
	bfqq->seek_history <<= 1;
	bfqq->seek_history |=
		get_sdist(bfqq->last_request_pos, rq) > BFQQ_SEEK_THR &&
		(!blk_queue_nonrot(bfqd->queue) ||
		 blk_rq_sectors(rq) < BFQQ_SECT_THR_NONROT);
}