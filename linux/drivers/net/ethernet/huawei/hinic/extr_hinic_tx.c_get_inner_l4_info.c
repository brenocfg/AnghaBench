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
union hinic_l4 {int /*<<< orphan*/  hdr; TYPE_1__* tcp; } ;
typedef  int u8 ;
typedef  int u32 ;
struct udphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sctphdr {int dummy; } ;
typedef  enum hinic_offload_type { ____Placeholder_hinic_offload_type } hinic_offload_type ;
typedef  enum hinic_l4_offload_type { ____Placeholder_hinic_l4_offload_type } hinic_l4_offload_type ;
struct TYPE_2__ {int doff; } ;

/* Variables and functions */
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int OFFLOAD_DISABLE ; 
 int SCTP_OFFLOAD_ENABLE ; 
 int TCP_OFFLOAD_ENABLE ; 
 int TRANSPORT_OFFSET (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int TX_OFFLOAD_CSUM ; 
 int UDP_OFFLOAD_ENABLE ; 

__attribute__((used)) static void get_inner_l4_info(struct sk_buff *skb, union hinic_l4 *l4,
			      enum hinic_offload_type offload_type, u8 l4_proto,
			      enum hinic_l4_offload_type *l4_offload,
			      u32 *l4_len, u32 *offset)
{
	*l4_offload = OFFLOAD_DISABLE;
	*offset = 0;
	*l4_len = 0;

	switch (l4_proto) {
	case IPPROTO_TCP:
		*l4_offload = TCP_OFFLOAD_ENABLE;
		/* doff in unit of 4B */
		*l4_len = l4->tcp->doff * 4;
		*offset = *l4_len + TRANSPORT_OFFSET(l4->hdr, skb);
		break;

	case IPPROTO_UDP:
		*l4_offload = UDP_OFFLOAD_ENABLE;
		*l4_len = sizeof(struct udphdr);
		*offset = TRANSPORT_OFFSET(l4->hdr, skb);
		break;

	case IPPROTO_SCTP:
		/* only csum offload support sctp */
		if (offload_type != TX_OFFLOAD_CSUM)
			break;

		*l4_offload = SCTP_OFFLOAD_ENABLE;
		*l4_len = sizeof(struct sctphdr);
		*offset = TRANSPORT_OFFSET(l4->hdr, skb);
		break;

	default:
		break;
	}
}