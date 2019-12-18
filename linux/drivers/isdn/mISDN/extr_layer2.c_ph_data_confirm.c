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
struct sk_buff {int dummy; } ;
struct mISDNhead {void* id; } ;
struct layer2 {void* down_id; int /*<<< orphan*/  flag; int /*<<< orphan*/  down_queue; int /*<<< orphan*/  l2m; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  EV_L2_ACK_PULL ; 
 int /*<<< orphan*/  FLG_L1_NOTREADY ; 
 void* MISDN_ID_NONE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ l2down_skb (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  mISDN_FsmEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* mISDN_HEAD_ID (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ph_data_confirm(struct layer2 *l2, struct mISDNhead *hh, struct sk_buff *skb) {
	struct sk_buff *nskb = skb;
	int ret = -EAGAIN;

	if (test_bit(FLG_L1_NOTREADY, &l2->flag)) {
		if (hh->id == l2->down_id) {
			nskb = skb_dequeue(&l2->down_queue);
			if (nskb) {
				l2->down_id = mISDN_HEAD_ID(nskb);
				if (l2down_skb(l2, nskb)) {
					dev_kfree_skb(nskb);
					l2->down_id = MISDN_ID_NONE;
				}
			} else
				l2->down_id = MISDN_ID_NONE;
			if (ret) {
				dev_kfree_skb(skb);
				ret = 0;
			}
			if (l2->down_id == MISDN_ID_NONE) {
				test_and_clear_bit(FLG_L1_NOTREADY, &l2->flag);
				mISDN_FsmEvent(&l2->l2m, EV_L2_ACK_PULL, NULL);
			}
		}
	}
	if (!test_and_set_bit(FLG_L1_NOTREADY, &l2->flag)) {
		nskb = skb_dequeue(&l2->down_queue);
		if (nskb) {
			l2->down_id = mISDN_HEAD_ID(nskb);
			if (l2down_skb(l2, nskb)) {
				dev_kfree_skb(nskb);
				l2->down_id = MISDN_ID_NONE;
				test_and_clear_bit(FLG_L1_NOTREADY, &l2->flag);
			}
		} else
			test_and_clear_bit(FLG_L1_NOTREADY, &l2->flag);
	}
	return ret;
}