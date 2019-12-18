#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union hinic_l4 {scalar_t__* hdr; } ;
union hinic_l3 {TYPE_2__* v6; scalar_t__* hdr; TYPE_1__* v4; } ;
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__* data; } ;
typedef  enum hinic_offload_type { ____Placeholder_hinic_offload_type } hinic_offload_type ;
typedef  enum hinic_l3_offload_type { ____Placeholder_hinic_l3_offload_type } hinic_l3_offload_type ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {scalar_t__ nexthdr; } ;
struct TYPE_3__ {int version; scalar_t__ protocol; } ;

/* Variables and functions */
 int IPV4_PKT_NO_CHKSUM_OFFLOAD ; 
 int IPV4_PKT_WITH_CHKSUM_OFFLOAD ; 
 int IPV6_PKT ; 
 int L3TYPE_UNKNOWN ; 
 int TX_OFFLOAD_CSUM ; 
 int /*<<< orphan*/  ipv6_skip_exthdr (struct sk_buff*,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_inner_l3_l4_type(struct sk_buff *skb, union hinic_l3 *ip,
				 union hinic_l4 *l4,
				 enum hinic_offload_type offload_type,
				 enum hinic_l3_offload_type *l3_type,
				 u8 *l4_proto)
{
	u8 *exthdr;

	if (ip->v4->version == 4) {
		*l3_type = (offload_type == TX_OFFLOAD_CSUM) ?
			   IPV4_PKT_NO_CHKSUM_OFFLOAD :
			   IPV4_PKT_WITH_CHKSUM_OFFLOAD;
		*l4_proto = ip->v4->protocol;
	} else if (ip->v4->version == 6) {
		*l3_type = IPV6_PKT;
		exthdr = ip->hdr + sizeof(*ip->v6);
		*l4_proto = ip->v6->nexthdr;
		if (exthdr != l4->hdr) {
			int start = exthdr - skb->data;
			__be16 frag_off;

			ipv6_skip_exthdr(skb, start, l4_proto, &frag_off);
		}
	} else {
		*l3_type = L3TYPE_UNKNOWN;
		*l4_proto = 0;
	}
}