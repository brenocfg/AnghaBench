#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mISDNhead {int /*<<< orphan*/  id; int /*<<< orphan*/  prim; } ;
struct dchannel {TYPE_1__* rx_skb; int /*<<< orphan*/  rqueue; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_RECVQUEUE ; 
 int /*<<< orphan*/  PH_DATA_IND ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  get_sapi_tei (int /*<<< orphan*/ ) ; 
 struct mISDNhead* mISDN_HEAD_P (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_event (struct dchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
recv_Dchannel(struct dchannel *dch)
{
	struct mISDNhead *hh;

	if (dch->rx_skb->len < 2) { /* at least 2 for sapi / tei */
		dev_kfree_skb(dch->rx_skb);
		dch->rx_skb = NULL;
		return;
	}
	hh = mISDN_HEAD_P(dch->rx_skb);
	hh->prim = PH_DATA_IND;
	hh->id = get_sapi_tei(dch->rx_skb->data);
	skb_queue_tail(&dch->rqueue, dch->rx_skb);
	dch->rx_skb = NULL;
	schedule_event(dch, FLG_RECVQUEUE);
}