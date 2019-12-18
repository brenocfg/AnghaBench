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
struct request_queue {struct nvme_ns* queuedata; } ;
struct request {int /*<<< orphan*/  ioprio; int /*<<< orphan*/  cmd_flags; } ;
struct nvme_nvm_command {int dummy; } ;
struct nvme_ns {int dummy; } ;
struct nvme_command {int dummy; } ;
struct nvm_rq {int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 int /*<<< orphan*/  IOPRIO_NORM ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  NVME_QID_ANY ; 
 int /*<<< orphan*/  REQ_FAILFAST_DRIVER ; 
 int /*<<< orphan*/  blk_rq_append_bio (struct request*,int /*<<< orphan*/ *) ; 
 struct request* nvme_alloc_request (struct request_queue*,struct nvme_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_nvm_rqtocmd (struct nvm_rq*,struct nvme_ns*,struct nvme_nvm_command*) ; 

__attribute__((used)) static struct request *nvme_nvm_alloc_request(struct request_queue *q,
					      struct nvm_rq *rqd,
					      struct nvme_nvm_command *cmd)
{
	struct nvme_ns *ns = q->queuedata;
	struct request *rq;

	nvme_nvm_rqtocmd(rqd, ns, cmd);

	rq = nvme_alloc_request(q, (struct nvme_command *)cmd, 0, NVME_QID_ANY);
	if (IS_ERR(rq))
		return rq;

	rq->cmd_flags &= ~REQ_FAILFAST_DRIVER;

	if (rqd->bio)
		blk_rq_append_bio(rq, &rqd->bio);
	else
		rq->ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, IOPRIO_NORM);

	return rq;
}