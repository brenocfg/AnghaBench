#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct cpl_fw4_ack {scalar_t__ credits; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {scalar_t__ initiator; } ;
struct c4iw_ep {TYPE_2__ com; int /*<<< orphan*/ * mpa_skb; TYPE_1__ mpa_attr; int /*<<< orphan*/  hwtid; int /*<<< orphan*/  dst; } ;
struct c4iw_dev {int dummy; } ;

/* Variables and functions */
 unsigned int GET_TID (struct cpl_fw4_ack*) ; 
 int /*<<< orphan*/  STOP_MPA_TIMER ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_2__*) ; 
 struct cpl_fw4_ack* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 struct c4iw_ep* get_ep_from_tid (struct c4iw_dev*,unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  state_read (TYPE_2__*) ; 
 int /*<<< orphan*/  stop_ep_timer (struct c4iw_ep*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fw4_ack(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct c4iw_ep *ep;
	struct cpl_fw4_ack *hdr = cplhdr(skb);
	u8 credits = hdr->credits;
	unsigned int tid = GET_TID(hdr);


	ep = get_ep_from_tid(dev, tid);
	if (!ep)
		return 0;
	pr_debug("ep %p tid %u credits %u\n",
		 ep, ep->hwtid, credits);
	if (credits == 0) {
		pr_debug("0 credit ack ep %p tid %u state %u\n",
			 ep, ep->hwtid, state_read(&ep->com));
		goto out;
	}

	dst_confirm(ep->dst);
	if (ep->mpa_skb) {
		pr_debug("last streaming msg ack ep %p tid %u state %u initiator %u freeing skb\n",
			 ep, ep->hwtid, state_read(&ep->com),
			 ep->mpa_attr.initiator ? 1 : 0);
		mutex_lock(&ep->com.mutex);
		kfree_skb(ep->mpa_skb);
		ep->mpa_skb = NULL;
		if (test_bit(STOP_MPA_TIMER, &ep->com.flags))
			stop_ep_timer(ep);
		mutex_unlock(&ep->com.mutex);
	}
out:
	c4iw_put_ep(&ep->com);
	return 0;
}