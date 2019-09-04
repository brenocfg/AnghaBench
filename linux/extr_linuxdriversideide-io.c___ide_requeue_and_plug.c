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
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_delay_queue (struct request_queue*,int) ; 
 scalar_t__ blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,struct request*) ; 

__attribute__((used)) static void __ide_requeue_and_plug(struct request_queue *q, struct request *rq)
{
	if (rq)
		blk_requeue_request(q, rq);
	if (rq || blk_peek_request(q)) {
		/* Use 3ms as that was the old plug delay */
		blk_delay_queue(q, 3);
	}
}