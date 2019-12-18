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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  ipv6_find_hdr (struct sk_buff*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int skb_checksum_start_offset (struct sk_buff*) ; 

__attribute__((used)) static inline bool ixgbe_ipv6_csum_is_sctp(struct sk_buff *skb)
{
	unsigned int offset = 0;

	ipv6_find_hdr(skb, &offset, IPPROTO_SCTP, NULL, NULL);

	return offset == skb_checksum_start_offset(skb);
}