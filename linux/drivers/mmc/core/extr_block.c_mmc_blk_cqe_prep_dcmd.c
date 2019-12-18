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
struct request {int /*<<< orphan*/  tag; } ;
struct mmc_request {int /*<<< orphan*/  tag; int /*<<< orphan*/ * cmd; } ;
struct mmc_blk_request {struct mmc_request mrq; int /*<<< orphan*/  cmd; } ;
struct mmc_queue_req {struct mmc_blk_request brq; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mmc_blk_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mmc_request *mmc_blk_cqe_prep_dcmd(struct mmc_queue_req *mqrq,
						 struct request *req)
{
	struct mmc_blk_request *brq = &mqrq->brq;

	memset(brq, 0, sizeof(*brq));

	brq->mrq.cmd = &brq->cmd;
	brq->mrq.tag = req->tag;

	return &brq->mrq;
}