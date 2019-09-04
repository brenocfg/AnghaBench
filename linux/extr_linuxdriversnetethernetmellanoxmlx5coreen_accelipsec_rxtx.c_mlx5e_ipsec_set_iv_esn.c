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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct xfrm_state {struct xfrm_replay_state_esn* replay_esn; } ;
struct xfrm_replay_state_esn {scalar_t__ oseq; } ;
struct TYPE_3__ {scalar_t__ low; scalar_t__ hi; } ;
struct xfrm_offload {TYPE_1__ seq; } ;
struct sk_buff {int dummy; } ;
struct ip_esp_hdr {int dummy; } ;
typedef  scalar_t__ __u32 ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_4__ {scalar_t__ gso_segs; } ;

/* Variables and functions */
 scalar_t__ MLX5E_IPSEC_ESN_SCOPE_MID ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_store_bits (struct sk_buff*,int,int /*<<< orphan*/ *,int) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void mlx5e_ipsec_set_iv_esn(struct sk_buff *skb, struct xfrm_state *x,
			    struct xfrm_offload *xo)
{
	struct xfrm_replay_state_esn *replay_esn = x->replay_esn;
	__u32 oseq = replay_esn->oseq;
	int iv_offset;
	__be64 seqno;
	u32 seq_hi;

	if (unlikely(skb_is_gso(skb) && oseq < MLX5E_IPSEC_ESN_SCOPE_MID &&
		     MLX5E_IPSEC_ESN_SCOPE_MID < (oseq - skb_shinfo(skb)->gso_segs))) {
		seq_hi = xo->seq.hi - 1;
	} else {
		seq_hi = xo->seq.hi;
	}

	/* Place the SN in the IV field */
	seqno = cpu_to_be64(xo->seq.low + ((u64)seq_hi << 32));
	iv_offset = skb_transport_offset(skb) + sizeof(struct ip_esp_hdr);
	skb_store_bits(skb, iv_offset, &seqno, 8);
}