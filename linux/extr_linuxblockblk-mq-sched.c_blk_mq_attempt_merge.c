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
struct request_queue {int dummy; } ;
struct blk_mq_ctx {int /*<<< orphan*/  rq_merged; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  lock; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ blk_mq_bio_list_merge (struct request_queue*,int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_mq_attempt_merge(struct request_queue *q,
				 struct blk_mq_ctx *ctx, struct bio *bio)
{
	lockdep_assert_held(&ctx->lock);

	if (blk_mq_bio_list_merge(q, &ctx->rq_list, bio)) {
		ctx->rq_merged++;
		return true;
	}

	return false;
}