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
struct request {int /*<<< orphan*/  q; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 int /*<<< orphan*/  blk_get_rl (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  blk_init_request_from_bio (struct request*,struct bio*) ; 
 int /*<<< orphan*/  blk_rq_set_rl (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blk_mq_bio_to_request(struct request *rq, struct bio *bio)
{
	blk_init_request_from_bio(rq, bio);

	blk_rq_set_rl(rq, blk_get_rl(rq->q, bio));

	blk_account_io_start(rq, true);
}