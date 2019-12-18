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
struct sk_buff {void* data; } ;
struct mlx5e_rq {TYPE_1__* stats; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {int ecn_mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int IP6_ECN_set_ce (struct sk_buff*,struct ipv6hdr*) ; 
 int IP_ECN_set_ce (struct iphdr*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_last_ethertype_ip (struct sk_buff*,int*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void mlx5e_enable_ecn(struct mlx5e_rq *rq, struct sk_buff *skb)
{
	int network_depth = 0;
	__be16 proto;
	void *ip;
	int rc;

	if (unlikely(!is_last_ethertype_ip(skb, &network_depth, &proto)))
		return;

	ip = skb->data + network_depth;
	rc = ((proto == htons(ETH_P_IP)) ? IP_ECN_set_ce((struct iphdr *)ip) :
					 IP6_ECN_set_ce(skb, (struct ipv6hdr *)ip));

	rq->stats->ecn_mark += !!rc;
}