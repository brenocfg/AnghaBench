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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct lan78xx_net {TYPE_1__* net; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int RX_CMD_A_FVTG_ ; 
 int RX_CMD_A_ICSM_ ; 
 int RX_CMD_B_CSUM_SHIFT_ ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void lan78xx_rx_csum_offload(struct lan78xx_net *dev,
				    struct sk_buff *skb,
				    u32 rx_cmd_a, u32 rx_cmd_b)
{
	/* HW Checksum offload appears to be flawed if used when not stripping
	 * VLAN headers. Drop back to S/W checksums under these conditions.
	 */
	if (!(dev->net->features & NETIF_F_RXCSUM) ||
	    unlikely(rx_cmd_a & RX_CMD_A_ICSM_) ||
	    ((rx_cmd_a & RX_CMD_A_FVTG_) &&
	     !(dev->net->features & NETIF_F_HW_VLAN_CTAG_RX))) {
		skb->ip_summed = CHECKSUM_NONE;
	} else {
		skb->csum = ntohs((u16)(rx_cmd_b >> RX_CMD_B_CSUM_SHIFT_));
		skb->ip_summed = CHECKSUM_COMPLETE;
	}
}