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
struct TYPE_5__ {int /*<<< orphan*/  status_error_len; } ;
struct TYPE_6__ {TYPE_1__ qword1; } ;
union iavf_rx_desc {TYPE_2__ wb; } ;
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iavf_vsi {TYPE_4__* back; TYPE_3__* netdev; } ;
struct iavf_rx_ptype_decoded {scalar_t__ outer_ip; scalar_t__ outer_ip_ver; int inner_prot; scalar_t__ known; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_csum_rx_error; } ;
struct TYPE_7__ {int features; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int IAVF_RXD_QW1_ERROR_MASK ; 
 int IAVF_RXD_QW1_ERROR_SHIFT ; 
 int IAVF_RXD_QW1_PTYPE_MASK ; 
 int IAVF_RXD_QW1_PTYPE_SHIFT ; 
 int IAVF_RXD_QW1_STATUS_MASK ; 
 int IAVF_RXD_QW1_STATUS_SHIFT ; 
 int /*<<< orphan*/  IAVF_RX_DESC_ERROR_EIPE_SHIFT ; 
 int /*<<< orphan*/  IAVF_RX_DESC_ERROR_IPE_SHIFT ; 
 int /*<<< orphan*/  IAVF_RX_DESC_ERROR_L4E_SHIFT ; 
 int /*<<< orphan*/  IAVF_RX_DESC_ERROR_PPRS_SHIFT ; 
 int /*<<< orphan*/  IAVF_RX_DESC_STATUS_IPV6EXADD_SHIFT ; 
 int /*<<< orphan*/  IAVF_RX_DESC_STATUS_L3L4P_SHIFT ; 
#define  IAVF_RX_PTYPE_INNER_PROT_SCTP 130 
#define  IAVF_RX_PTYPE_INNER_PROT_TCP 129 
#define  IAVF_RX_PTYPE_INNER_PROT_UDP 128 
 scalar_t__ IAVF_RX_PTYPE_OUTER_IP ; 
 scalar_t__ IAVF_RX_PTYPE_OUTER_IPV4 ; 
 scalar_t__ IAVF_RX_PTYPE_OUTER_IPV6 ; 
 int NETIF_F_RXCSUM ; 
 struct iavf_rx_ptype_decoded decode_rx_desc_ptype (int) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void iavf_rx_checksum(struct iavf_vsi *vsi,
				    struct sk_buff *skb,
				    union iavf_rx_desc *rx_desc)
{
	struct iavf_rx_ptype_decoded decoded;
	u32 rx_error, rx_status;
	bool ipv4, ipv6;
	u8 ptype;
	u64 qword;

	qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
	ptype = (qword & IAVF_RXD_QW1_PTYPE_MASK) >> IAVF_RXD_QW1_PTYPE_SHIFT;
	rx_error = (qword & IAVF_RXD_QW1_ERROR_MASK) >>
		   IAVF_RXD_QW1_ERROR_SHIFT;
	rx_status = (qword & IAVF_RXD_QW1_STATUS_MASK) >>
		    IAVF_RXD_QW1_STATUS_SHIFT;
	decoded = decode_rx_desc_ptype(ptype);

	skb->ip_summed = CHECKSUM_NONE;

	skb_checksum_none_assert(skb);

	/* Rx csum enabled and ip headers found? */
	if (!(vsi->netdev->features & NETIF_F_RXCSUM))
		return;

	/* did the hardware decode the packet and checksum? */
	if (!(rx_status & BIT(IAVF_RX_DESC_STATUS_L3L4P_SHIFT)))
		return;

	/* both known and outer_ip must be set for the below code to work */
	if (!(decoded.known && decoded.outer_ip))
		return;

	ipv4 = (decoded.outer_ip == IAVF_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == IAVF_RX_PTYPE_OUTER_IPV4);
	ipv6 = (decoded.outer_ip == IAVF_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == IAVF_RX_PTYPE_OUTER_IPV6);

	if (ipv4 &&
	    (rx_error & (BIT(IAVF_RX_DESC_ERROR_IPE_SHIFT) |
			 BIT(IAVF_RX_DESC_ERROR_EIPE_SHIFT))))
		goto checksum_fail;

	/* likely incorrect csum if alternate IP extension headers found */
	if (ipv6 &&
	    rx_status & BIT(IAVF_RX_DESC_STATUS_IPV6EXADD_SHIFT))
		/* don't increment checksum err here, non-fatal err */
		return;

	/* there was some L4 error, count error and punt packet to the stack */
	if (rx_error & BIT(IAVF_RX_DESC_ERROR_L4E_SHIFT))
		goto checksum_fail;

	/* handle packets that were not able to be checksummed due
	 * to arrival speed, in this case the stack can compute
	 * the csum.
	 */
	if (rx_error & BIT(IAVF_RX_DESC_ERROR_PPRS_SHIFT))
		return;

	/* Only report checksum unnecessary for TCP, UDP, or SCTP */
	switch (decoded.inner_prot) {
	case IAVF_RX_PTYPE_INNER_PROT_TCP:
	case IAVF_RX_PTYPE_INNER_PROT_UDP:
	case IAVF_RX_PTYPE_INNER_PROT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		/* fall though */
	default:
		break;
	}

	return;

checksum_fail:
	vsi->back->hw_csum_rx_error++;
}