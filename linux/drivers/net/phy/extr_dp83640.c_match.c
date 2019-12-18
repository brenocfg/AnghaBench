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
struct rxts {int msgtype; scalar_t__ seqid; int hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP83640_PACKET_HASH_LEN ; 
 int DP83640_PACKET_HASH_OFFSET ; 
 unsigned int ETH_HLEN ; 
 unsigned int IP6_HLEN ; 
 unsigned int IPV4_HLEN (int*) ; 
 int OFF_PTP_CONTROL ; 
 unsigned int OFF_PTP_SEQUENCE_ID ; 
#define  PTP_CLASS_IPV4 130 
#define  PTP_CLASS_IPV6 129 
#define  PTP_CLASS_L2 128 
 unsigned int PTP_CLASS_PMASK ; 
 unsigned int PTP_CLASS_V1 ; 
 unsigned int PTP_CLASS_VLAN ; 
 unsigned int UDP_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 int ether_crc (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ntohs (int) ; 
 int* skb_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int match(struct sk_buff *skb, unsigned int type, struct rxts *rxts)
{
	u16 *seqid, hash;
	unsigned int offset = 0;
	u8 *msgtype, *data = skb_mac_header(skb);

	/* check sequenceID, messageType, 12 bit hash of offset 20-29 */

	if (type & PTP_CLASS_VLAN)
		offset += VLAN_HLEN;

	switch (type & PTP_CLASS_PMASK) {
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
		return 0;
	}

	if (skb->len + ETH_HLEN < offset + OFF_PTP_SEQUENCE_ID + sizeof(*seqid))
		return 0;

	if (unlikely(type & PTP_CLASS_V1))
		msgtype = data + offset + OFF_PTP_CONTROL;
	else
		msgtype = data + offset;
	if (rxts->msgtype != (*msgtype & 0xf))
		return 0;

	seqid = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);
	if (rxts->seqid != ntohs(*seqid))
		return 0;

	hash = ether_crc(DP83640_PACKET_HASH_LEN,
			 data + offset + DP83640_PACKET_HASH_OFFSET) >> 20;
	if (rxts->hash != hash)
		return 0;

	return 1;
}