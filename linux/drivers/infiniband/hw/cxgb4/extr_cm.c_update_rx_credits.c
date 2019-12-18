#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct cpl_rx_data_ack {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct c4iw_ep {int rcv_win; TYPE_2__ com; int /*<<< orphan*/  ctrlq_idx; int /*<<< orphan*/  hwtid; } ;
struct TYPE_3__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RCV_BUFSIZ_M ; 
 int RX_DACK_CHANGE_F ; 
 int RX_DACK_MODE_V (int /*<<< orphan*/ ) ; 
 int RX_FORCE_ACK_F ; 
 int /*<<< orphan*/  c4iw_ofld_send (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb_mk_rx_data_ack (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dack_mode ; 
 struct sk_buff* get_skb (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int roundup (int,int) ; 

__attribute__((used)) static int update_rx_credits(struct c4iw_ep *ep, u32 credits)
{
	struct sk_buff *skb;
	u32 wrlen = roundup(sizeof(struct cpl_rx_data_ack), 16);
	u32 credit_dack;

	pr_debug("ep %p tid %u credits %u\n",
		 ep, ep->hwtid, credits);
	skb = get_skb(NULL, wrlen, GFP_KERNEL);
	if (!skb) {
		pr_err("update_rx_credits - cannot alloc skb!\n");
		return 0;
	}

	/*
	 * If we couldn't specify the entire rcv window at connection setup
	 * due to the limit in the number of bits in the RCV_BUFSIZ field,
	 * then add the overage in to the credits returned.
	 */
	if (ep->rcv_win > RCV_BUFSIZ_M * 1024)
		credits += ep->rcv_win - RCV_BUFSIZ_M * 1024;

	credit_dack = credits | RX_FORCE_ACK_F | RX_DACK_CHANGE_F |
		      RX_DACK_MODE_V(dack_mode);

	cxgb_mk_rx_data_ack(skb, wrlen, ep->hwtid, ep->ctrlq_idx,
			    credit_dack);

	c4iw_ofld_send(&ep->com.dev->rdev, skb);
	return credits;
}