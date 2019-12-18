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
struct TYPE_6__ {void* first_seq; } ;
struct TYPE_7__ {TYPE_2__ send; } ;
struct mlx5e_tls_metadata {TYPE_3__ content; } ;
typedef  struct mlx5e_tls_metadata u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  syndrome ;
struct tcphdr {int /*<<< orphan*/  seq; } ;
struct sk_buff {int len; int /*<<< orphan*/  queue_mapping; int /*<<< orphan*/  ip_summed; struct mlx5e_tls_metadata* data; TYPE_1__* dev; } ;
struct iphdr {void* tot_len; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  rcd_sn ;
typedef  struct mlx5e_tls_metadata __be64 ;
struct TYPE_8__ {int gso_size; int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_segs; } ;
struct TYPE_5__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 struct mlx5e_tls_metadata SYNDROME_SYNC ; 
 int /*<<< orphan*/  htonl (int) ; 
 void* htons (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct mlx5e_tls_metadata*,struct mlx5e_tls_metadata*,int) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void mlx5e_tls_complete_sync_skb(struct sk_buff *skb,
					struct sk_buff *nskb, u32 tcp_seq,
					int headln, __be64 rcd_sn)
{
	struct mlx5e_tls_metadata *pet;
	u8 syndrome = SYNDROME_SYNC;
	struct iphdr *iph;
	struct tcphdr *th;
	int data_len, mss;

	nskb->dev = skb->dev;
	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb, skb_network_offset(skb));
	skb_set_transport_header(nskb, skb_transport_offset(skb));
	memcpy(nskb->data, skb->data, headln);
	memcpy(nskb->data + headln, &rcd_sn, sizeof(rcd_sn));

	iph = ip_hdr(nskb);
	iph->tot_len = htons(nskb->len - skb_network_offset(nskb));
	th = tcp_hdr(nskb);
	data_len = nskb->len - headln;
	tcp_seq -= data_len;
	th->seq = htonl(tcp_seq);

	mss = nskb->dev->mtu - (headln - skb_network_offset(nskb));
	skb_shinfo(nskb)->gso_size = 0;
	if (data_len > mss) {
		skb_shinfo(nskb)->gso_size = mss;
		skb_shinfo(nskb)->gso_segs = DIV_ROUND_UP(data_len, mss);
	}
	skb_shinfo(nskb)->gso_type = skb_shinfo(skb)->gso_type;

	pet = (struct mlx5e_tls_metadata *)(nskb->data + sizeof(struct ethhdr));
	memcpy(pet, &syndrome, sizeof(syndrome));
	pet->content.send.first_seq = htons(tcp_seq);

	/* MLX5 devices don't care about the checksum partial start, offset
	 * and pseudo header
	 */
	nskb->ip_summed = CHECKSUM_PARTIAL;

	nskb->queue_mapping = skb->queue_mapping;
}