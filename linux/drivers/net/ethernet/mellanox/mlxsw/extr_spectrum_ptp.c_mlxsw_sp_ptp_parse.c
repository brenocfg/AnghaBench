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
typedef  int u16 ;
struct sk_buff {unsigned int len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 unsigned int ETH_HLEN ; 
 unsigned int IP6_HLEN ; 
 unsigned int IPV4_HLEN (int*) ; 
#define  PTP_CLASS_IPV4 132 
#define  PTP_CLASS_IPV6 131 
#define  PTP_CLASS_L2 130 
 unsigned int PTP_CLASS_PMASK ; 
#define  PTP_CLASS_V1 129 
#define  PTP_CLASS_V2 128 
 unsigned int PTP_CLASS_VLAN ; 
 unsigned int PTP_CLASS_VMASK ; 
 unsigned int UDP_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 unsigned int ptp_classify_raw (struct sk_buff*) ; 
 int* skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int mlxsw_sp_ptp_parse(struct sk_buff *skb,
			      u8 *p_domain_number,
			      u8 *p_message_type,
			      u16 *p_sequence_id)
{
	unsigned int offset = 0;
	unsigned int ptp_class;
	u8 *data;

	data = skb_mac_header(skb);
	ptp_class = ptp_classify_raw(skb);

	switch (ptp_class & PTP_CLASS_VMASK) {
	case PTP_CLASS_V1:
	case PTP_CLASS_V2:
		break;
	default:
		return -ERANGE;
	}

	if (ptp_class & PTP_CLASS_VLAN)
		offset += VLAN_HLEN;

	switch (ptp_class & PTP_CLASS_PMASK) {
	case PTP_CLASS_IPV4:
		offset += ETH_HLEN + IPV4_HLEN(data + offset) + UDP_HLEN;
		break;
	case PTP_CLASS_IPV6:
		offset += ETH_HLEN + IP6_HLEN + UDP_HLEN;
		break;
	case PTP_CLASS_L2:
		offset += ETH_HLEN;
		break;
	default:
		return -ERANGE;
	}

	/* PTP header is 34 bytes. */
	if (skb->len < offset + 34)
		return -EINVAL;

	*p_message_type = data[offset] & 0x0f;
	*p_domain_number = data[offset + 4];
	*p_sequence_id = (u16)(data[offset + 30]) << 8 | data[offset + 31];
	return 0;
}