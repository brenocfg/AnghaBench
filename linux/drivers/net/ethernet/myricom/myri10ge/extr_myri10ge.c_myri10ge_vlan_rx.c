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
typedef  int /*<<< orphan*/  u8 ;
struct vlan_ethhdr {scalar_t__ h_vlan_proto; int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; int /*<<< orphan*/  csum; } ;
struct net_device {int features; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_2__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  MXGEFW_PAD ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_size_sub (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline void
myri10ge_vlan_rx(struct net_device *dev, void *addr, struct sk_buff *skb)
{
	u8 *va;
	struct vlan_ethhdr *veh;
	skb_frag_t *frag;
	__wsum vsum;

	va = addr;
	va += MXGEFW_PAD;
	veh = (struct vlan_ethhdr *)va;
	if ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) ==
	    NETIF_F_HW_VLAN_CTAG_RX &&
	    veh->h_vlan_proto == htons(ETH_P_8021Q)) {
		/* fixup csum if needed */
		if (skb->ip_summed == CHECKSUM_COMPLETE) {
			vsum = csum_partial(va + ETH_HLEN, VLAN_HLEN, 0);
			skb->csum = csum_sub(skb->csum, vsum);
		}
		/* pop tag */
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(veh->h_vlan_TCI));
		memmove(va + VLAN_HLEN, va, 2 * ETH_ALEN);
		skb->len -= VLAN_HLEN;
		skb->data_len -= VLAN_HLEN;
		frag = skb_shinfo(skb)->frags;
		skb_frag_off_add(frag, VLAN_HLEN);
		skb_frag_size_sub(frag, VLAN_HLEN);
	}
}