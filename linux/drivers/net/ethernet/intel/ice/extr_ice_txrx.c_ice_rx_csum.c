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
struct TYPE_5__ {int /*<<< orphan*/  status_error0; } ;
union ice_32b_rx_flex_desc {TYPE_1__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct ice_rx_ptype_decoded {scalar_t__ outer_ip; scalar_t__ outer_ip_ver; int inner_prot; scalar_t__ known; } ;
struct ice_ring {TYPE_4__* vsi; TYPE_2__* netdev; } ;
struct TYPE_8__ {TYPE_3__* back; } ;
struct TYPE_7__ {int /*<<< orphan*/  hw_csum_rx_error; } ;
struct TYPE_6__ {int features; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ICE_RX_FLEX_DESC_STATUS0_IPV6EXADD_S ; 
 int /*<<< orphan*/  ICE_RX_FLEX_DESC_STATUS0_L3L4P_S ; 
 int /*<<< orphan*/  ICE_RX_FLEX_DESC_STATUS0_XSUM_EIPE_S ; 
 int /*<<< orphan*/  ICE_RX_FLEX_DESC_STATUS0_XSUM_IPE_S ; 
 int /*<<< orphan*/  ICE_RX_FLEX_DESC_STATUS0_XSUM_L4E_S ; 
#define  ICE_RX_PTYPE_INNER_PROT_SCTP 130 
#define  ICE_RX_PTYPE_INNER_PROT_TCP 129 
#define  ICE_RX_PTYPE_INNER_PROT_UDP 128 
 scalar_t__ ICE_RX_PTYPE_OUTER_IP ; 
 scalar_t__ ICE_RX_PTYPE_OUTER_IPV4 ; 
 scalar_t__ ICE_RX_PTYPE_OUTER_IPV6 ; 
 int NETIF_F_RXCSUM ; 
 struct ice_rx_ptype_decoded ice_decode_rx_desc_ptype (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static void
ice_rx_csum(struct ice_ring *ring, struct sk_buff *skb,
	    union ice_32b_rx_flex_desc *rx_desc, u8 ptype)
{
	struct ice_rx_ptype_decoded decoded;
	u32 rx_error, rx_status;
	bool ipv4, ipv6;

	rx_status = le16_to_cpu(rx_desc->wb.status_error0);
	rx_error = rx_status;

	decoded = ice_decode_rx_desc_ptype(ptype);

	/* Start with CHECKSUM_NONE and by default csum_level = 0 */
	skb->ip_summed = CHECKSUM_NONE;
	skb_checksum_none_assert(skb);

	/* check if Rx checksum is enabled */
	if (!(ring->netdev->features & NETIF_F_RXCSUM))
		return;

	/* check if HW has decoded the packet and checksum */
	if (!(rx_status & BIT(ICE_RX_FLEX_DESC_STATUS0_L3L4P_S)))
		return;

	if (!(decoded.known && decoded.outer_ip))
		return;

	ipv4 = (decoded.outer_ip == ICE_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == ICE_RX_PTYPE_OUTER_IPV4);
	ipv6 = (decoded.outer_ip == ICE_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == ICE_RX_PTYPE_OUTER_IPV6);

	if (ipv4 && (rx_error & (BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_IPE_S) |
				 BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_EIPE_S))))
		goto checksum_fail;
	else if (ipv6 && (rx_status &
		 (BIT(ICE_RX_FLEX_DESC_STATUS0_IPV6EXADD_S))))
		goto checksum_fail;

	/* check for L4 errors and handle packets that were not able to be
	 * checksummed due to arrival speed
	 */
	if (rx_error & BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_L4E_S))
		goto checksum_fail;

	/* Only report checksum unnecessary for TCP, UDP, or SCTP */
	switch (decoded.inner_prot) {
	case ICE_RX_PTYPE_INNER_PROT_TCP:
	case ICE_RX_PTYPE_INNER_PROT_UDP:
	case ICE_RX_PTYPE_INNER_PROT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	default:
		break;
	}
	return;

checksum_fail:
	ring->vsi->back->hw_csum_rx_error++;
}