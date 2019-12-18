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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan743x_ptp_tx_ts_complete (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_ptp_tx_ts_enqueue_skb (struct lan743x_adapter*,struct sk_buff*,int) ; 

void lan743x_ptp_tx_timestamp_skb(struct lan743x_adapter *adapter,
				  struct sk_buff *skb, bool ignore_sync)
{
	lan743x_ptp_tx_ts_enqueue_skb(adapter, skb, ignore_sync);

	lan743x_ptp_tx_ts_complete(adapter);
}