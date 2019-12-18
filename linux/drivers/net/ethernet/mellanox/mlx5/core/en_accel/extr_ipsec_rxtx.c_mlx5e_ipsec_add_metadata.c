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
struct sk_buff {int mac_header; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct mlx5e_ipsec_metadata {TYPE_1__ content; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5e_ipsec_metadata* ERR_PTR (int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MLX5E_METADATA_ETHER_TYPE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_cow_head (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5e_ipsec_metadata *mlx5e_ipsec_add_metadata(struct sk_buff *skb)
{
	struct mlx5e_ipsec_metadata *mdata;
	struct ethhdr *eth;

	if (unlikely(skb_cow_head(skb, sizeof(*mdata))))
		return ERR_PTR(-ENOMEM);

	eth = (struct ethhdr *)skb_push(skb, sizeof(*mdata));
	skb->mac_header -= sizeof(*mdata);
	mdata = (struct mlx5e_ipsec_metadata *)(eth + 1);

	memmove(skb->data, skb->data + sizeof(*mdata),
		2 * ETH_ALEN);

	eth->h_proto = cpu_to_be16(MLX5E_METADATA_ETHER_TYPE);

	memset(mdata->content.raw, 0, sizeof(mdata->content.raw));
	return mdata;
}