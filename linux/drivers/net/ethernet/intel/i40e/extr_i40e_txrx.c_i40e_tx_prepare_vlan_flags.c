#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vlan_hdr {scalar_t__ h_vlan_encapsulated_proto; int /*<<< orphan*/  h_vlan_TCI; } ;
struct vlan_ethhdr {scalar_t__ h_vlan_TCI; } ;
struct sk_buff {scalar_t__ protocol; int priority; scalar_t__ data; } ;
struct i40e_ring {TYPE_3__* vsi; TYPE_1__* netdev; } ;
typedef  int /*<<< orphan*/  _vhdr ;
typedef  scalar_t__ __be16 ;
struct TYPE_6__ {TYPE_2__* back; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int ETH_P_8021Q ; 
 int I40E_FLAG_DCB_ENABLED ; 
 int I40E_TX_FLAGS_HW_VLAN ; 
 int I40E_TX_FLAGS_SW_VLAN ; 
 int I40E_TX_FLAGS_VLAN_PRIO_MASK ; 
 int I40E_TX_FLAGS_VLAN_PRIO_SHIFT ; 
 int I40E_TX_FLAGS_VLAN_SHIFT ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int TC_PRIO_CONTROL ; 
 scalar_t__ htons (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct vlan_hdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct vlan_hdr*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static inline int i40e_tx_prepare_vlan_flags(struct sk_buff *skb,
					     struct i40e_ring *tx_ring,
					     u32 *flags)
{
	__be16 protocol = skb->protocol;
	u32  tx_flags = 0;

	if (protocol == htons(ETH_P_8021Q) &&
	    !(tx_ring->netdev->features & NETIF_F_HW_VLAN_CTAG_TX)) {
		/* When HW VLAN acceleration is turned off by the user the
		 * stack sets the protocol to 8021q so that the driver
		 * can take any steps required to support the SW only
		 * VLAN handling.  In our case the driver doesn't need
		 * to take any further steps so just set the protocol
		 * to the encapsulated ethertype.
		 */
		skb->protocol = vlan_get_protocol(skb);
		goto out;
	}

	/* if we have a HW VLAN tag being added, default to the HW one */
	if (skb_vlan_tag_present(skb)) {
		tx_flags |= skb_vlan_tag_get(skb) << I40E_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= I40E_TX_FLAGS_HW_VLAN;
	/* else if it is a SW VLAN, check the next protocol and store the tag */
	} else if (protocol == htons(ETH_P_8021Q)) {
		struct vlan_hdr *vhdr, _vhdr;

		vhdr = skb_header_pointer(skb, ETH_HLEN, sizeof(_vhdr), &_vhdr);
		if (!vhdr)
			return -EINVAL;

		protocol = vhdr->h_vlan_encapsulated_proto;
		tx_flags |= ntohs(vhdr->h_vlan_TCI) << I40E_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= I40E_TX_FLAGS_SW_VLAN;
	}

	if (!(tx_ring->vsi->back->flags & I40E_FLAG_DCB_ENABLED))
		goto out;

	/* Insert 802.1p priority into VLAN header */
	if ((tx_flags & (I40E_TX_FLAGS_HW_VLAN | I40E_TX_FLAGS_SW_VLAN)) ||
	    (skb->priority != TC_PRIO_CONTROL)) {
		tx_flags &= ~I40E_TX_FLAGS_VLAN_PRIO_MASK;
		tx_flags |= (skb->priority & 0x7) <<
				I40E_TX_FLAGS_VLAN_PRIO_SHIFT;
		if (tx_flags & I40E_TX_FLAGS_SW_VLAN) {
			struct vlan_ethhdr *vhdr;
			int rc;

			rc = skb_cow_head(skb, 0);
			if (rc < 0)
				return rc;
			vhdr = (struct vlan_ethhdr *)skb->data;
			vhdr->h_vlan_TCI = htons(tx_flags >>
						 I40E_TX_FLAGS_VLAN_SHIFT);
		} else {
			tx_flags |= I40E_TX_FLAGS_HW_VLAN;
		}
	}

out:
	*flags = tx_flags;
	return 0;
}