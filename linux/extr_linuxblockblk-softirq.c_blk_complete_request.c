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
 int /*<<< orphan*/  __blk_complete_request (struct request*) ; 
 int /*<<< orphan*/  blk_mark_rq_complete (struct request*) ; 
 int /*<<< orphan*/  blk_should_fake_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void blk_complete_request(struct request *req)
{
	if (unlikely(blk_should_fake_timeout(req->q)))
		return;
	if (!blk_mark_rq_complete(req))
		__blk_complete_request(req);
}