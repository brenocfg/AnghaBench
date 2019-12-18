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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct e1000_adapter {int /*<<< orphan*/  hw_csum_good; int /*<<< orphan*/  hw_csum_err; TYPE_1__* netdev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int E1000_RXD_ERR_IPE ; 
 int E1000_RXD_ERR_TCPE ; 
 int E1000_RXD_STAT_IXSM ; 
 int E1000_RXD_STAT_TCPCS ; 
 int E1000_RXD_STAT_UDPCS ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static void e1000_rx_checksum(struct e1000_adapter *adapter, u32 status_err,
			      struct sk_buff *skb)
{
	u16 status = (u16)status_err;
	u8 errors = (u8)(status_err >> 24);

	skb_checksum_none_assert(skb);

	/* Rx checksum disabled */
	if (!(adapter->netdev->features & NETIF_F_RXCSUM))
		return;

	/* Ignore Checksum bit is set */
	if (status & E1000_RXD_STAT_IXSM)
		return;

	/* TCP/UDP checksum error bit or IP checksum error bit is set */
	if (errors & (E1000_RXD_ERR_TCPE | E1000_RXD_ERR_IPE)) {
		/* let the stack verify checksum errors */
		adapter->hw_csum_err++;
		return;
	}

	/* TCP/UDP Checksum has not been calculated */
	if (!(status & (E1000_RXD_STAT_TCPCS | E1000_RXD_STAT_UDPCS)))
		return;

	/* It must be a TCP or UDP packet with a valid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	adapter->hw_csum_good++;
}