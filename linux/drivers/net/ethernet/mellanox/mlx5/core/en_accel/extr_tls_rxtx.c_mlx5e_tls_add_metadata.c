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
struct sk_buff {int mac_header; scalar_t__ data; } ;
struct TYPE_3__ {int syndrome_swid; } ;
struct TYPE_4__ {TYPE_1__ send; } ;
struct mlx5e_tls_metadata {TYPE_2__ content; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  int __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MLX5E_METADATA_ETHER_TYPE ; 
 int SYNDROME_OFFLOAD_REQUIRED ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int mlx5e_tls_add_metadata(struct sk_buff *skb, __be32 swid)
{
	struct mlx5e_tls_metadata *pet;
	struct ethhdr *eth;

	if (skb_cow_head(skb, sizeof(struct mlx5e_tls_metadata)))
		return -ENOMEM;

	eth = (struct ethhdr *)skb_push(skb, sizeof(struct mlx5e_tls_metadata));
	skb->mac_header -= sizeof(struct mlx5e_tls_metadata);
	pet = (struct mlx5e_tls_metadata *)(eth + 1);

	memmove(skb->data, skb->data + sizeof(struct mlx5e_tls_metadata),
		2 * ETH_ALEN);

	eth->h_proto = cpu_to_be16(MLX5E_METADATA_ETHER_TYPE);
	pet->content.send.syndrome_swid =
		htonl(SYNDROME_OFFLOAD_REQUIRED << 24) | swid;

	return 0;
}