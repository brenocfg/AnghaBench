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
struct TYPE_2__ {int /*<<< orphan*/  bchannels; } ;
struct dchannel {int maxlen; int /*<<< orphan*/  workq; TYPE_1__ dev; int /*<<< orphan*/  rqueue; int /*<<< orphan*/  squeue; void* phfunc; scalar_t__ tx_idx; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/ * hw; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_HDLC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dchannel_bh ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mISDN_initdchannel(struct dchannel *ch, int maxlen, void *phf)
{
	test_and_set_bit(FLG_HDLC, &ch->Flags);
	ch->maxlen = maxlen;
	ch->hw = NULL;
	ch->rx_skb = NULL;
	ch->tx_skb = NULL;
	ch->tx_idx = 0;
	ch->phfunc = phf;
	skb_queue_head_init(&ch->squeue);
	skb_queue_head_init(&ch->rqueue);
	INIT_LIST_HEAD(&ch->dev.bchannels);
	INIT_WORK(&ch->workq, dchannel_bh);
	return 0;
}