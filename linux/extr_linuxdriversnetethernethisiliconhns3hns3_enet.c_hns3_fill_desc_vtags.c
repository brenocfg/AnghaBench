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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct vlan_ethhdr {int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {scalar_t__ protocol; int priority; scalar_t__ data; } ;
struct hns3_enet_ring {TYPE_4__* tqp; } ;
struct TYPE_8__ {TYPE_3__* handle; } ;
struct TYPE_6__ {TYPE_1__* netdev; } ;
struct TYPE_7__ {TYPE_2__ kinfo; } ;
struct TYPE_5__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  HNS3_TXD_OVLAN_B ; 
 int /*<<< orphan*/  HNS3_TXD_VLAN_B ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 void* vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static int hns3_fill_desc_vtags(struct sk_buff *skb,
				struct hns3_enet_ring *tx_ring,
				u32 *inner_vlan_flag,
				u32 *out_vlan_flag,
				u16 *inner_vtag,
				u16 *out_vtag)
{
#define HNS3_TX_VLAN_PRIO_SHIFT 13

	if (skb->protocol == htons(ETH_P_8021Q) &&
	    !(tx_ring->tqp->handle->kinfo.netdev->features &
	    NETIF_F_HW_VLAN_CTAG_TX)) {
		/* When HW VLAN acceleration is turned off, and the stack
		 * sets the protocol to 802.1q, the driver just need to
		 * set the protocol to the encapsulated ethertype.
		 */
		skb->protocol = vlan_get_protocol(skb);
		return 0;
	}

	if (skb_vlan_tag_present(skb)) {
		u16 vlan_tag;

		vlan_tag = skb_vlan_tag_get(skb);
		vlan_tag |= (skb->priority & 0x7) << HNS3_TX_VLAN_PRIO_SHIFT;

		/* Based on hw strategy, use out_vtag in two layer tag case,
		 * and use inner_vtag in one tag case.
		 */
		if (skb->protocol == htons(ETH_P_8021Q)) {
			hnae3_set_bit(*out_vlan_flag, HNS3_TXD_OVLAN_B, 1);
			*out_vtag = vlan_tag;
		} else {
			hnae3_set_bit(*inner_vlan_flag, HNS3_TXD_VLAN_B, 1);
			*inner_vtag = vlan_tag;
		}
	} else if (skb->protocol == htons(ETH_P_8021Q)) {
		struct vlan_ethhdr *vhdr;
		int rc;

		rc = skb_cow_head(skb, 0);
		if (rc < 0)
			return rc;
		vhdr = (struct vlan_ethhdr *)skb->data;
		vhdr->h_vlan_TCI |= cpu_to_be16((skb->priority & 0x7)
					<< HNS3_TX_VLAN_PRIO_SHIFT);
	}

	skb->protocol = vlan_get_protocol(skb);
	return 0;
}