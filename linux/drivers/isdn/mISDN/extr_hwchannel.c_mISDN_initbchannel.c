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
struct bchannel {unsigned short minlen; unsigned short next_minlen; unsigned short init_minlen; unsigned short maxlen; unsigned short next_maxlen; unsigned short init_maxlen; int /*<<< orphan*/  workq; int /*<<< orphan*/ * next_skb; scalar_t__ rcount; int /*<<< orphan*/  rqueue; scalar_t__ tx_idx; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/ * hw; scalar_t__ Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bchannel_bh ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

int
mISDN_initbchannel(struct bchannel *ch, unsigned short maxlen,
		   unsigned short minlen)
{
	ch->Flags = 0;
	ch->minlen = minlen;
	ch->next_minlen = minlen;
	ch->init_minlen = minlen;
	ch->maxlen = maxlen;
	ch->next_maxlen = maxlen;
	ch->init_maxlen = maxlen;
	ch->hw = NULL;
	ch->rx_skb = NULL;
	ch->tx_skb = NULL;
	ch->tx_idx = 0;
	skb_queue_head_init(&ch->rqueue);
	ch->rcount = 0;
	ch->next_skb = NULL;
	INIT_WORK(&ch->workq, bchannel_bh);
	return 0;
}