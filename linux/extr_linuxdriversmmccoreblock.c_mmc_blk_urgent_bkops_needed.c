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
struct TYPE_6__ {int* resp; } ;
struct TYPE_5__ {int* resp; } ;
struct TYPE_7__ {TYPE_2__ stop; TYPE_1__ cmd; } ;
struct mmc_queue_req {TYPE_3__ brq; } ;
struct mmc_queue {TYPE_4__* card; } ;
struct TYPE_8__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int R1_EXCEPTION_EVENT ; 
 scalar_t__ mmc_card_mmc (TYPE_4__*) ; 
 int /*<<< orphan*/  mmc_host_is_spi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mmc_blk_urgent_bkops_needed(struct mmc_queue *mq,
					struct mmc_queue_req *mqrq)
{
	return mmc_card_mmc(mq->card) && !mmc_host_is_spi(mq->card->host) &&
	       (mqrq->brq.cmd.resp[0] & R1_EXCEPTION_EVENT ||
		mqrq->brq.stop.resp[0] & R1_EXCEPTION_EVENT);
}