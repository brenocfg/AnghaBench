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
struct mISDNhead {scalar_t__ prim; } ;
struct layer2 {int /*<<< orphan*/  down_id; int /*<<< orphan*/  down_queue; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L1_NOTREADY ; 
 scalar_t__ PH_DATA_REQ ; 
 int l2down_skb (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  mISDN_HEAD_ID (struct sk_buff*) ; 
 struct mISDNhead* mISDN_HEAD_P (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
l2down_raw(struct layer2 *l2, struct sk_buff *skb)
{
	struct mISDNhead *hh = mISDN_HEAD_P(skb);

	if (hh->prim == PH_DATA_REQ) {
		if (test_and_set_bit(FLG_L1_NOTREADY, &l2->flag)) {
			skb_queue_tail(&l2->down_queue, skb);
			return 0;
		}
		l2->down_id = mISDN_HEAD_ID(skb);
	}
	return l2down_skb(l2, skb);
}