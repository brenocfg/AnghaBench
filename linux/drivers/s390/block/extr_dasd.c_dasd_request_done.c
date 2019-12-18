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
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dasd_request_done(struct request *req)
{
	blk_mq_end_request(req, 0);
	blk_mq_run_hw_queues(req->q, true);
}