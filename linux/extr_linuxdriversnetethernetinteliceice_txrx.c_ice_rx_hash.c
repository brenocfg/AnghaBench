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
struct TYPE_4__ {scalar_t__ rxdid; } ;
union ice_32b_rx_flex_desc {TYPE_2__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ice_ring {TYPE_1__* netdev; } ;
struct ice_32b_rx_flex_desc_nic {int /*<<< orphan*/  rss_hash; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 scalar_t__ ICE_RXDID_FLEX_NIC ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  ice_ptype_to_htype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_rx_hash(struct ice_ring *rx_ring, union ice_32b_rx_flex_desc *rx_desc,
	    struct sk_buff *skb, u8 rx_ptype)
{
	struct ice_32b_rx_flex_desc_nic *nic_mdid;
	u32 hash;

	if (!(rx_ring->netdev->features & NETIF_F_RXHASH))
		return;

	if (rx_desc->wb.rxdid != ICE_RXDID_FLEX_NIC)
		return;

	nic_mdid = (struct ice_32b_rx_flex_desc_nic *)rx_desc;
	hash = le32_to_cpu(nic_mdid->rss_hash);
	skb_set_hash(skb, hash, ice_ptype_to_htype(rx_ptype));
}