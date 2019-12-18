#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct cmdq_pkt* data; int /*<<< orphan*/  cb; } ;
struct TYPE_6__ {void* data; int /*<<< orphan*/  cb; } ;
struct cmdq_pkt {int /*<<< orphan*/  cmd_buf_size; int /*<<< orphan*/  pa_base; TYPE_2__ async_cb; TYPE_1__ cb; scalar_t__ cl; } ;
struct cmdq_client {scalar_t__ timeout_ms; TYPE_4__* chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  pkt_cnt; } ;
typedef  int /*<<< orphan*/  cmdq_async_flush_cb ;
struct TYPE_9__ {TYPE_3__* mbox; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CMDQ_NO_TIMEOUT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int cmdq_pkt_finalize (struct cmdq_pkt*) ; 
 int /*<<< orphan*/  cmdq_pkt_flush_async_cb ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mbox_client_txdone (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_send_message (TYPE_4__*,struct cmdq_pkt*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cmdq_pkt_flush_async(struct cmdq_pkt *pkt, cmdq_async_flush_cb cb,
			 void *data)
{
	int err;
	unsigned long flags = 0;
	struct cmdq_client *client = (struct cmdq_client *)pkt->cl;

	err = cmdq_pkt_finalize(pkt);
	if (err < 0)
		return err;

	pkt->cb.cb = cb;
	pkt->cb.data = data;
	pkt->async_cb.cb = cmdq_pkt_flush_async_cb;
	pkt->async_cb.data = pkt;

	dma_sync_single_for_device(client->chan->mbox->dev, pkt->pa_base,
				   pkt->cmd_buf_size, DMA_TO_DEVICE);

	if (client->timeout_ms != CMDQ_NO_TIMEOUT) {
		spin_lock_irqsave(&client->lock, flags);
		if (client->pkt_cnt++ == 0)
			mod_timer(&client->timer, jiffies +
				  msecs_to_jiffies(client->timeout_ms));
		spin_unlock_irqrestore(&client->lock, flags);
	}

	mbox_send_message(client->chan, pkt);
	/* We can send next packet immediately, so just call txdone. */
	mbox_client_txdone(client->chan, 0);

	return 0;
}