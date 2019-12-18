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
union hinic_l4 {int /*<<< orphan*/  hdr; } ;
union hinic_l3 {void* hdr; TYPE_1__* v4; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct hinic_sq_task {int dummy; } ;
typedef  enum hinic_l4_offload_type { ____Placeholder_hinic_l4_offload_type } hinic_l4_offload_type ;
typedef  enum hinic_l3_offload_type { ____Placeholder_hinic_l3_offload_type } hinic_l3_offload_type ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int IPV4_PKT_NO_CHKSUM_OFFLOAD ; 
 int IPV6_PKT ; 
 int L3TYPE_UNKNOWN ; 
 int /*<<< orphan*/  TUNNEL_UDP_NO_CSUM ; 
 int /*<<< orphan*/  TX_OFFLOAD_CSUM ; 
 int /*<<< orphan*/  get_inner_l3_l4_type (struct sk_buff*,union hinic_l3*,union hinic_l4*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_inner_l4_info (struct sk_buff*,union hinic_l4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  hinic_set_cs_inner_l4 (struct hinic_sq_task*,scalar_t__*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hinic_task_set_inner_l3 (struct hinic_sq_task*,int,scalar_t__) ; 
 int /*<<< orphan*/  hinic_task_set_outter_l3 (struct hinic_sq_task*,int,scalar_t__) ; 
 int /*<<< orphan*/  hinic_task_set_tunnel_l4 (struct hinic_sq_task*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* skb_inner_network_header (struct sk_buff*) ; 
 scalar_t__ skb_inner_network_header_len (struct sk_buff*) ; 
 scalar_t__ skb_inner_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_inner_transport_header (struct sk_buff*) ; 
 void* skb_network_header (struct sk_buff*) ; 
 scalar_t__ skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int offload_csum(struct hinic_sq_task *task, u32 *queue_info,
			struct sk_buff *skb)
{
	enum hinic_l4_offload_type l4_offload;
	u32 offset, l4_len, network_hdr_len;
	enum hinic_l3_offload_type l3_type;
	union hinic_l3 ip;
	union hinic_l4 l4;
	u8 l4_proto;

	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return 0;

	if (skb->encapsulation) {
		u32 l4_tunnel_len;

		ip.hdr = skb_network_header(skb);

		if (ip.v4->version == 4)
			l3_type = IPV4_PKT_NO_CHKSUM_OFFLOAD;
		else if (ip.v4->version == 6)
			l3_type = IPV6_PKT;
		else
			l3_type = L3TYPE_UNKNOWN;

		hinic_task_set_outter_l3(task, l3_type,
					 skb_network_header_len(skb));

		l4_tunnel_len = skb_inner_network_offset(skb) -
				skb_transport_offset(skb);

		hinic_task_set_tunnel_l4(task, TUNNEL_UDP_NO_CSUM,
					 l4_tunnel_len);

		ip.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);
		network_hdr_len = skb_inner_network_header_len(skb);
	} else {
		ip.hdr = skb_network_header(skb);
		l4.hdr = skb_transport_header(skb);
		network_hdr_len = skb_network_header_len(skb);
	}

	get_inner_l3_l4_type(skb, &ip, &l4, TX_OFFLOAD_CSUM, &l3_type,
			     &l4_proto);

	hinic_task_set_inner_l3(task, l3_type, network_hdr_len);

	get_inner_l4_info(skb, &l4, TX_OFFLOAD_CSUM, l4_proto, &l4_offload,
			  &l4_len, &offset);

	hinic_set_cs_inner_l4(task, queue_info, l4_offload, l4_len, offset);

	return 1;
}