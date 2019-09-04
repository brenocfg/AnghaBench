#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* resp; scalar_t__ error; } ;
struct TYPE_7__ {scalar_t__ error; } ;
struct TYPE_6__ {scalar_t__ error; } ;
struct TYPE_5__ {scalar_t__ error; } ;
struct mmc_blk_request {TYPE_4__ cmd; TYPE_3__ data; TYPE_2__ stop; TYPE_1__ sbc; } ;

/* Variables and functions */
 int CMD_ERRORS ; 
 int /*<<< orphan*/  mmc_blk_eval_resp_error (struct mmc_blk_request*) ; 

__attribute__((used)) static inline bool mmc_blk_rq_error(struct mmc_blk_request *brq)
{
	mmc_blk_eval_resp_error(brq);

	return brq->sbc.error || brq->cmd.error || brq->stop.error ||
	       brq->data.error || brq->cmd.resp[0] & CMD_ERRORS;
}