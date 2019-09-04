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
typedef  scalar_t__ u16 ;
struct udphdr {int dummy; } ;
struct sk_buff {scalar_t__ len; scalar_t__ encapsulation; } ;
struct mlx5e_txqsq {struct mlx5e_sq_stats* stats; } ;
struct mlx5e_sq_stats {int /*<<< orphan*/  tso_bytes; int /*<<< orphan*/  tso_packets; int /*<<< orphan*/  tso_inner_bytes; int /*<<< orphan*/  tso_inner_packets; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int SKB_GSO_UDP_L4 ; 
 scalar_t__ inner_tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ skb_inner_transport_offset (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static inline u16
mlx5e_tx_get_gso_ihs(struct mlx5e_txqsq *sq, struct sk_buff *skb)
{
	struct mlx5e_sq_stats *stats = sq->stats;
	u16 ihs;

	if (skb->encapsulation) {
		ihs = skb_inner_transport_offset(skb) + inner_tcp_hdrlen(skb);
		stats->tso_inner_packets++;
		stats->tso_inner_bytes += skb->len - ihs;
	} else {
		if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
			ihs = skb_transport_offset(skb) + sizeof(struct udphdr);
		else
			ihs = skb_transport_offset(skb) + tcp_hdrlen(skb);
		stats->tso_packets++;
		stats->tso_bytes += skb->len - ihs;
	}

	return ihs;
}