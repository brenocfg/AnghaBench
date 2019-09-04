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
struct xgbe_prv_data {int /*<<< orphan*/  tstamp_lock; int /*<<< orphan*/  tx_tstamp_skb; } ;
struct xgbe_packet_data {int /*<<< orphan*/  attributes; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP ; 
 int /*<<< orphan*/  SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES ; 
 scalar_t__ XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xgbe_prep_tx_tstamp(struct xgbe_prv_data *pdata,
				struct sk_buff *skb,
				struct xgbe_packet_data *packet)
{
	unsigned long flags;

	if (XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES, PTP)) {
		spin_lock_irqsave(&pdata->tstamp_lock, flags);
		if (pdata->tx_tstamp_skb) {
			/* Another timestamp in progress, ignore this one */
			XGMAC_SET_BITS(packet->attributes,
				       TX_PACKET_ATTRIBUTES, PTP, 0);
		} else {
			pdata->tx_tstamp_skb = skb_get(skb);
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		}
		spin_unlock_irqrestore(&pdata->tstamp_lock, flags);
	}

	skb_tx_timestamp(skb);
}