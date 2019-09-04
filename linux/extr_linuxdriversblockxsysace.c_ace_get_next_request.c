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
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 

__attribute__((used)) static struct request *ace_get_next_request(struct request_queue *q)
{
	struct request *req;

	while ((req = blk_peek_request(q)) != NULL) {
		if (!blk_rq_is_passthrough(req))
			break;
		blk_start_request(req);
		__blk_end_request_all(req, BLK_STS_IOERR);
	}
	return req;
}