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

/* Variables and functions */
 int /*<<< orphan*/  __dm_mq_kick_requeue_list (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 

__attribute__((used)) static void dm_mq_delay_requeue_request(struct request *rq, unsigned long msecs)
{
	blk_mq_requeue_request(rq, false);
	__dm_mq_kick_requeue_list(rq->q, msecs);
}