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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  seqid ;
typedef  int /*<<< orphan*/  lo ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 unsigned int IPV4_HLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ OFF_PTP_SEQUENCE_ID ; 
 int OFF_PTP_SOURCE_UUID ; 
 scalar_t__ PTP_CLASS_V1_IPV4 ; 
 unsigned int UDP_HLEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ ntohl (scalar_t__) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 scalar_t__ ptp_classify_raw (struct sk_buff*) ; 

__attribute__((used)) static int ixp_ptp_match(struct sk_buff *skb, u16 uid_hi, u32 uid_lo, u16 seqid)
{
	u8 *data = skb->data;
	unsigned int offset;
	u16 *hi, *id;
	u32 lo;

	if (ptp_classify_raw(skb) != PTP_CLASS_V1_IPV4)
		return 0;

	offset = ETH_HLEN + IPV4_HLEN(data) + UDP_HLEN;

	if (skb->len < offset + OFF_PTP_SEQUENCE_ID + sizeof(seqid))
		return 0;

	hi = (u16 *)(data + offset + OFF_PTP_SOURCE_UUID);
	id = (u16 *)(data + offset + OFF_PTP_SEQUENCE_ID);

	memcpy(&lo, &hi[1], sizeof(lo));

	return (uid_hi == ntohs(*hi) &&
		uid_lo == ntohl(lo) &&
		seqid  == ntohs(*id));
}