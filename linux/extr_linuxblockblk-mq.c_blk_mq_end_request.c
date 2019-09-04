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
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void blk_mq_end_request(struct request *rq, blk_status_t error)
{
	if (blk_update_request(rq, error, blk_rq_bytes(rq)))
		BUG();
	__blk_mq_end_request(rq, error);
}