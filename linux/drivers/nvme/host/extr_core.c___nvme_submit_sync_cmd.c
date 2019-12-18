#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union nvme_result {int dummy; } nvme_result ;
struct request_queue {int dummy; } ;
struct request {unsigned int timeout; int /*<<< orphan*/  q; } ;
struct nvme_command {int dummy; } ;
typedef  int /*<<< orphan*/  blk_mq_req_flags_t ;
struct TYPE_2__ {int flags; int status; union nvme_result result; } ;

/* Variables and functions */
 unsigned int ADMIN_TIMEOUT ; 
 int EINTR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int NVME_REQ_CANCELLED ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int blk_rq_map_kern (struct request_queue*,struct request*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 struct request* nvme_alloc_request (struct request_queue*,struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_execute_rq_polled (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 TYPE_1__* nvme_req (struct request*) ; 

int __nvme_submit_sync_cmd(struct request_queue *q, struct nvme_command *cmd,
		union nvme_result *result, void *buffer, unsigned bufflen,
		unsigned timeout, int qid, int at_head,
		blk_mq_req_flags_t flags, bool poll)
{
	struct request *req;
	int ret;

	req = nvme_alloc_request(q, cmd, flags, qid);
	if (IS_ERR(req))
		return PTR_ERR(req);

	req->timeout = timeout ? timeout : ADMIN_TIMEOUT;

	if (buffer && bufflen) {
		ret = blk_rq_map_kern(q, req, buffer, bufflen, GFP_KERNEL);
		if (ret)
			goto out;
	}

	if (poll)
		nvme_execute_rq_polled(req->q, NULL, req, at_head);
	else
		blk_execute_rq(req->q, NULL, req, at_head);
	if (result)
		*result = nvme_req(req)->result;
	if (nvme_req(req)->flags & NVME_REQ_CANCELLED)
		ret = -EINTR;
	else
		ret = nvme_req(req)->status;
 out:
	blk_mq_free_request(req);
	return ret;
}