#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {struct nvm_rq* end_io_data; } ;
struct nvm_rq {int /*<<< orphan*/  error; int /*<<< orphan*/  ppa_status; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  u64; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  status; TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvm_end_io (struct nvm_rq*) ; 
 TYPE_2__* nvme_req (struct request*) ; 

__attribute__((used)) static void nvme_nvm_end_io(struct request *rq, blk_status_t status)
{
	struct nvm_rq *rqd = rq->end_io_data;

	rqd->ppa_status = le64_to_cpu(nvme_req(rq)->result.u64);
	rqd->error = nvme_req(rq)->status;
	nvm_end_io(rqd);

	kfree(nvme_req(rq)->cmd);
	blk_mq_free_request(rq);
}