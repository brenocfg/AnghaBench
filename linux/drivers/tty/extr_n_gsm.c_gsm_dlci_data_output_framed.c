#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct gsm_mux {int mtu; int /*<<< orphan*/  ftype; } ;
struct gsm_msg {int /*<<< orphan*/ * data; } ;
struct gsm_dlci {int adaption; TYPE_1__* skb; int /*<<< orphan*/  skb_list; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __gsm_data_queue (struct gsm_dlci*,struct gsm_msg*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_1__*) ; 
 struct gsm_msg* gsm_data_alloc (struct gsm_mux*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int gsm_dlci_data_output_framed(struct gsm_mux *gsm,
						struct gsm_dlci *dlci)
{
	struct gsm_msg *msg;
	u8 *dp;
	int len, size;
	int last = 0, first = 0;
	int overhead = 0;

	/* One byte per frame is used for B/F flags */
	if (dlci->adaption == 4)
		overhead = 1;

	/* dlci->skb is locked by tx_lock */
	if (dlci->skb == NULL) {
		dlci->skb = skb_dequeue_tail(&dlci->skb_list);
		if (dlci->skb == NULL)
			return 0;
		first = 1;
	}
	len = dlci->skb->len + overhead;

	/* MTU/MRU count only the data bits */
	if (len > gsm->mtu) {
		if (dlci->adaption == 3) {
			/* Over long frame, bin it */
			dev_kfree_skb_any(dlci->skb);
			dlci->skb = NULL;
			return 0;
		}
		len = gsm->mtu;
	} else
		last = 1;

	size = len + overhead;
	msg = gsm_data_alloc(gsm, dlci->addr, size, gsm->ftype);

	/* FIXME: need a timer or something to kick this so it can't
	   get stuck with no work outstanding and no buffer free */
	if (msg == NULL) {
		skb_queue_tail(&dlci->skb_list, dlci->skb);
		dlci->skb = NULL;
		return -ENOMEM;
	}
	dp = msg->data;

	if (dlci->adaption == 4) { /* Interruptible framed (Packetised Data) */
		/* Flag byte to carry the start/end info */
		*dp++ = last << 7 | first << 6 | 1;	/* EA */
		len--;
	}
	memcpy(dp, dlci->skb->data, len);
	skb_pull(dlci->skb, len);
	__gsm_data_queue(dlci, msg);
	if (last) {
		dev_kfree_skb_any(dlci->skb);
		dlci->skb = NULL;
	}
	return size;
}