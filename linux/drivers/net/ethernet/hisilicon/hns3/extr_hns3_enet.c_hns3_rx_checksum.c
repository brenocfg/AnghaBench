#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int csum_level; int /*<<< orphan*/  ip_summed; } ;
struct net_device {int features; } ;
struct TYPE_8__ {int /*<<< orphan*/  l3l4_csum_err; } ;
struct hns3_enet_ring {int /*<<< orphan*/  syncp; TYPE_4__ stats; TYPE_3__* tqp; } ;
struct TYPE_7__ {TYPE_2__* handle; } ;
struct TYPE_5__ {struct net_device* netdev; } ;
struct TYPE_6__ {TYPE_1__ kinfo; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int HNS3_L3_TYPE_IPV4 ; 
 int HNS3_L3_TYPE_IPV6 ; 
 int HNS3_L4_TYPE_SCTP ; 
 int HNS3_L4_TYPE_TCP ; 
 int HNS3_L4_TYPE_UDP ; 
#define  HNS3_OL4_TYPE_MAC_IN_UDP 130 
#define  HNS3_OL4_TYPE_NO_TUN 129 
#define  HNS3_OL4_TYPE_NVGRE 128 
 int /*<<< orphan*/  HNS3_RXD_L3E_B ; 
 int /*<<< orphan*/  HNS3_RXD_L3ID_M ; 
 int /*<<< orphan*/  HNS3_RXD_L3ID_S ; 
 int /*<<< orphan*/  HNS3_RXD_L3L4P_B ; 
 int /*<<< orphan*/  HNS3_RXD_L4E_B ; 
 int /*<<< orphan*/  HNS3_RXD_L4ID_M ; 
 int /*<<< orphan*/  HNS3_RXD_L4ID_S ; 
 int /*<<< orphan*/  HNS3_RXD_OL3E_B ; 
 int /*<<< orphan*/  HNS3_RXD_OL4E_B ; 
 int /*<<< orphan*/  HNS3_RXD_OL4ID_M ; 
 int /*<<< orphan*/  HNS3_RXD_OL4ID_S ; 
 int NETIF_F_RXCSUM ; 
 int hnae3_get_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hns3_rx_checksum(struct hns3_enet_ring *ring, struct sk_buff *skb,
			     u32 l234info, u32 bd_base_info, u32 ol_info)
{
	struct net_device *netdev = ring->tqp->handle->kinfo.netdev;
	int l3_type, l4_type;
	int ol4_type;

	skb->ip_summed = CHECKSUM_NONE;

	skb_checksum_none_assert(skb);

	if (!(netdev->features & NETIF_F_RXCSUM))
		return;

	/* check if hardware has done checksum */
	if (!(bd_base_info & BIT(HNS3_RXD_L3L4P_B)))
		return;

	if (unlikely(l234info & (BIT(HNS3_RXD_L3E_B) | BIT(HNS3_RXD_L4E_B) |
				 BIT(HNS3_RXD_OL3E_B) |
				 BIT(HNS3_RXD_OL4E_B)))) {
		u64_stats_update_begin(&ring->syncp);
		ring->stats.l3l4_csum_err++;
		u64_stats_update_end(&ring->syncp);

		return;
	}

	ol4_type = hnae3_get_field(ol_info, HNS3_RXD_OL4ID_M,
				   HNS3_RXD_OL4ID_S);
	switch (ol4_type) {
	case HNS3_OL4_TYPE_MAC_IN_UDP:
	case HNS3_OL4_TYPE_NVGRE:
		skb->csum_level = 1;
		/* fall through */
	case HNS3_OL4_TYPE_NO_TUN:
		l3_type = hnae3_get_field(l234info, HNS3_RXD_L3ID_M,
					  HNS3_RXD_L3ID_S);
		l4_type = hnae3_get_field(l234info, HNS3_RXD_L4ID_M,
					  HNS3_RXD_L4ID_S);

		/* Can checksum ipv4 or ipv6 + UDP/TCP/SCTP packets */
		if ((l3_type == HNS3_L3_TYPE_IPV4 ||
		     l3_type == HNS3_L3_TYPE_IPV6) &&
		    (l4_type == HNS3_L4_TYPE_UDP ||
		     l4_type == HNS3_L4_TYPE_TCP ||
		     l4_type == HNS3_L4_TYPE_SCTP))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		break;
	default:
		break;
	}
}