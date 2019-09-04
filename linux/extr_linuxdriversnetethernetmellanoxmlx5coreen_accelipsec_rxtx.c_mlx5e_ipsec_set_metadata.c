#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfrm_offload {int /*<<< orphan*/  proto; } ;
struct tcphdr {int /*<<< orphan*/  seq; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  len; int /*<<< orphan*/  inner_transport_header; int /*<<< orphan*/  inner_network_header; int /*<<< orphan*/  transport_header; int /*<<< orphan*/  network_header; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  mss_inv; int /*<<< orphan*/  esp_next_proto; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct mlx5e_ipsec_metadata {TYPE_2__ content; int /*<<< orphan*/  syndrome; } ;
struct ip_esp_hdr {int /*<<< orphan*/  seq_no; } ;
struct TYPE_6__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_IPSEC_TX_SYNDROME_OFFLOAD ; 
 int /*<<< orphan*/  MLX5E_IPSEC_TX_SYNDROME_OFFLOAD_WITH_LSO_TCP ; 
 int /*<<< orphan*/  htons (int) ; 
 struct tcphdr* inner_tcp_hdr (struct sk_buff*) ; 
 struct ip_esp_hdr* ip_esp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  mlx5e_ipsec_mss_inv (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void mlx5e_ipsec_set_metadata(struct sk_buff *skb,
				     struct mlx5e_ipsec_metadata *mdata,
				     struct xfrm_offload *xo)
{
	struct ip_esp_hdr *esph;
	struct tcphdr *tcph;

	if (skb_is_gso(skb)) {
		/* Add LSO metadata indication */
		esph = ip_esp_hdr(skb);
		tcph = inner_tcp_hdr(skb);
		netdev_dbg(skb->dev, "   Offloading GSO packet outer L3 %u; L4 %u; Inner L3 %u; L4 %u\n",
			   skb->network_header,
			   skb->transport_header,
			   skb->inner_network_header,
			   skb->inner_transport_header);
		netdev_dbg(skb->dev, "   Offloading GSO packet of len %u; mss %u; TCP sp %u dp %u seq 0x%x ESP seq 0x%x\n",
			   skb->len, skb_shinfo(skb)->gso_size,
			   ntohs(tcph->source), ntohs(tcph->dest),
			   ntohl(tcph->seq), ntohl(esph->seq_no));
		mdata->syndrome = MLX5E_IPSEC_TX_SYNDROME_OFFLOAD_WITH_LSO_TCP;
		mdata->content.tx.mss_inv = mlx5e_ipsec_mss_inv(skb);
		mdata->content.tx.seq = htons(ntohl(tcph->seq) & 0xFFFF);
	} else {
		mdata->syndrome = MLX5E_IPSEC_TX_SYNDROME_OFFLOAD;
	}
	mdata->content.tx.esp_next_proto = xo->proto;

	netdev_dbg(skb->dev, "   TX metadata syndrome %u proto %u mss_inv %04x seq %04x\n",
		   mdata->syndrome, mdata->content.tx.esp_next_proto,
		   ntohs(mdata->content.tx.mss_inv),
		   ntohs(mdata->content.tx.seq));
}