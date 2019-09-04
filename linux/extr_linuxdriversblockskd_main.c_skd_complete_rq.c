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
struct skd_request_context {int /*<<< orphan*/  status; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 struct skd_request_context* blk_mq_rq_to_pdu (struct request*) ; 

__attribute__((used)) static void skd_complete_rq(struct request *req)
{
	struct skd_request_context *skreq = blk_mq_rq_to_pdu(req);

	blk_mq_end_request(req, skreq->status);
}