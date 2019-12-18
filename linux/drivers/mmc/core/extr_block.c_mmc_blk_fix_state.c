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
struct mmc_blk_request {int /*<<< orphan*/  data; } ;
struct mmc_queue_req {struct mmc_blk_request brq; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int card_busy_detect (struct mmc_card*,unsigned int,struct request*,int /*<<< orphan*/ *) ; 
 unsigned int mmc_blk_data_timeout_ms (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_blk_send_stop (struct mmc_card*,unsigned int) ; 
 int /*<<< orphan*/  mmc_retune_hold_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_retune_release (int /*<<< orphan*/ ) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static int mmc_blk_fix_state(struct mmc_card *card, struct request *req)
{
	struct mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	struct mmc_blk_request *brq = &mqrq->brq;
	unsigned int timeout = mmc_blk_data_timeout_ms(card->host, &brq->data);
	int err;

	mmc_retune_hold_now(card->host);

	mmc_blk_send_stop(card, timeout);

	err = card_busy_detect(card, timeout, req, NULL);

	mmc_retune_release(card->host);

	return err;
}