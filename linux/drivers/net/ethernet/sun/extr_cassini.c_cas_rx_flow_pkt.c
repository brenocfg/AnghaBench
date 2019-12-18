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
typedef  int u64 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cas {struct sk_buff_head* rx_flows; } ;

/* Variables and functions */
 int CAS_VAL (int /*<<< orphan*/ ,int const) ; 
 int N_RX_FLOWS ; 
 int const RX_COMP1_RELEASE_FLOW ; 
 int /*<<< orphan*/  RX_COMP3_FLOWID ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  cas_skb_release (struct sk_buff*) ; 

__attribute__((used)) static inline void cas_rx_flow_pkt(struct cas *cp, const u64 *words,
				   struct sk_buff *skb)
{
	int flowid = CAS_VAL(RX_COMP3_FLOWID, words[2]) & (N_RX_FLOWS - 1);
	struct sk_buff_head *flow = &cp->rx_flows[flowid];

	/* this is protected at a higher layer, so no need to
	 * do any additional locking here. stick the buffer
	 * at the end.
	 */
	__skb_queue_tail(flow, skb);
	if (words[0] & RX_COMP1_RELEASE_FLOW) {
		while ((skb = __skb_dequeue(flow))) {
			cas_skb_release(skb);
		}
	}
}