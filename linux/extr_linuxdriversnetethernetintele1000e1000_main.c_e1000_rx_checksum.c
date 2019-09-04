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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {int /*<<< orphan*/  hw_csum_good; int /*<<< orphan*/  hw_csum_err; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int E1000_RXD_ERR_TCPE ; 
 int E1000_RXD_STAT_IXSM ; 
 int E1000_RXD_STAT_TCPCS ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void e1000_rx_checksum(struct e1000_adapter *adapter, u32 status_err,
			      u32 csum, struct sk_buff *skb)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 status = (u16)status_err;
	u8 errors = (u8)(status_err >> 24);

	skb_checksum_none_assert(skb);

	/* 82543 or newer only */
	if (unlikely(hw->mac_type < e1000_82543))
		return;
	/* Ignore Checksum bit is set */
	if (unlikely(status & E1000_RXD_STAT_IXSM))
		return;
	/* TCP/UDP checksum error bit is set */
	if (unlikely(errors & E1000_RXD_ERR_TCPE)) {
		/* let the stack verify checksum errors */
		adapter->hw_csum_err++;
		return;
	}
	/* TCP/UDP Checksum has not been calculated */
	if (!(status & E1000_RXD_STAT_TCPCS))
		return;

	/* It must be a TCP or UDP packet with a valid checksum */
	if (likely(status & E1000_RXD_STAT_TCPCS)) {
		/* TCP checksum is good */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
	adapter->hw_csum_good++;
}