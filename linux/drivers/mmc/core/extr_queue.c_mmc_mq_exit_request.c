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
struct mmc_queue {int /*<<< orphan*/  queue; } ;
struct blk_mq_tag_set {struct mmc_queue* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_exit_request (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void mmc_mq_exit_request(struct blk_mq_tag_set *set, struct request *req,
				unsigned int hctx_idx)
{
	struct mmc_queue *mq = set->driver_data;

	mmc_exit_request(mq->queue, req);
}