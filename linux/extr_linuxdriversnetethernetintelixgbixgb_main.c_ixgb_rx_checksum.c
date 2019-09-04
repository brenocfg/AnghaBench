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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct ixgb_rx_desc {int status; int errors; } ;
struct ixgb_adapter {int /*<<< orphan*/  hw_csum_rx_good; int /*<<< orphan*/  hw_csum_rx_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int IXGB_RX_DESC_ERRORS_TCPE ; 
 int IXGB_RX_DESC_STATUS_IXSM ; 
 int IXGB_RX_DESC_STATUS_TCPCS ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static void
ixgb_rx_checksum(struct ixgb_adapter *adapter,
                 struct ixgb_rx_desc *rx_desc,
                 struct sk_buff *skb)
{
	/* Ignore Checksum bit is set OR
	 * TCP Checksum has not been calculated
	 */
	if ((rx_desc->status & IXGB_RX_DESC_STATUS_IXSM) ||
	   (!(rx_desc->status & IXGB_RX_DESC_STATUS_TCPCS))) {
		skb_checksum_none_assert(skb);
		return;
	}

	/* At this point we know the hardware did the TCP checksum */
	/* now look at the TCP checksum error bit */
	if (rx_desc->errors & IXGB_RX_DESC_ERRORS_TCPE) {
		/* let the stack verify checksum errors */
		skb_checksum_none_assert(skb);
		adapter->hw_csum_rx_error++;
	} else {
		/* TCP checksum is good */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		adapter->hw_csum_rx_good++;
	}
}