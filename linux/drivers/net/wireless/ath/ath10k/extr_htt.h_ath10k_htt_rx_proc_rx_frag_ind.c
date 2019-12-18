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
struct sk_buff {int dummy; } ;
struct htt_rx_fragment_indication {int dummy; } ;
struct ath10k_htt {TYPE_1__* rx_ops; } ;
struct TYPE_2__ {int (* htt_rx_proc_rx_frag_ind ) (struct ath10k_htt*,struct htt_rx_fragment_indication*,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (struct ath10k_htt*,struct htt_rx_fragment_indication*,struct sk_buff*) ; 

__attribute__((used)) static inline bool ath10k_htt_rx_proc_rx_frag_ind(struct ath10k_htt *htt,
						  struct htt_rx_fragment_indication *rx,
						  struct sk_buff *skb)
{
	if (!htt->rx_ops->htt_rx_proc_rx_frag_ind)
		return true;

	return htt->rx_ops->htt_rx_proc_rx_frag_ind(htt, rx, skb);
}