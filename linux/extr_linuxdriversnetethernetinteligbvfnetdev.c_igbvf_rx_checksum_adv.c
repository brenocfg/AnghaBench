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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct igbvf_adapter {int flags; int /*<<< orphan*/  hw_csum_good; int /*<<< orphan*/  hw_csum_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int E1000_RXDEXT_STATERR_IPE ; 
 int E1000_RXDEXT_STATERR_TCPE ; 
 int E1000_RXD_STAT_IXSM ; 
 int E1000_RXD_STAT_TCPCS ; 
 int E1000_RXD_STAT_UDPCS ; 
 int IGBVF_FLAG_RX_CSUM_DISABLED ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void igbvf_rx_checksum_adv(struct igbvf_adapter *adapter,
					 u32 status_err, struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);

	/* Ignore Checksum bit is set or checksum is disabled through ethtool */
	if ((status_err & E1000_RXD_STAT_IXSM) ||
	    (adapter->flags & IGBVF_FLAG_RX_CSUM_DISABLED))
		return;

	/* TCP/UDP checksum error bit is set */
	if (status_err &
	    (E1000_RXDEXT_STATERR_TCPE | E1000_RXDEXT_STATERR_IPE)) {
		/* let the stack verify checksum errors */
		adapter->hw_csum_err++;
		return;
	}

	/* It must be a TCP or UDP packet with a valid checksum */
	if (status_err & (E1000_RXD_STAT_TCPCS | E1000_RXD_STAT_UDPCS))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	adapter->hw_csum_good++;
}