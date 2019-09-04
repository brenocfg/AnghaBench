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
typedef  int u64 ;
struct xfrm_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ hi; scalar_t__ low; } ;
struct xfrm_offload {TYPE_1__ seq; } ;
struct sk_buff {int dummy; } ;
struct ip_esp_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  skb_store_bits (struct sk_buff*,int,int /*<<< orphan*/ *,int) ; 
 int skb_transport_offset (struct sk_buff*) ; 

void mlx5e_ipsec_set_iv(struct sk_buff *skb, struct xfrm_state *x,
			struct xfrm_offload *xo)
{
	int iv_offset;
	__be64 seqno;

	/* Place the SN in the IV field */
	seqno = cpu_to_be64(xo->seq.low + ((u64)xo->seq.hi << 32));
	iv_offset = skb_transport_offset(skb) + sizeof(struct ip_esp_hdr);
	skb_store_bits(skb, iv_offset, &seqno, 8);
}