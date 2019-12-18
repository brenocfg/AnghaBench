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
struct skb_shared_info {int nr_frags; scalar_t__ gso_size; } ;
struct sk_buff {int data; scalar_t__ encapsulation; } ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {TYPE_1__* prof; } ;
struct TYPE_2__ {int /*<<< orphan*/  inline_thold; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int CTRL_SIZE ; 
 int DS_SIZE ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*) ; 
 int inline_size (struct sk_buff const*) ; 
 int inner_tcp_hdrlen (struct sk_buff const*) ; 
 int is_inline (int /*<<< orphan*/ ,struct sk_buff const*,struct skb_shared_info const*,void**) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct mlx4_en_priv*) ; 
 int skb_headlen (struct sk_buff const*) ; 
 int skb_inner_transport_header (struct sk_buff const*) ; 
 int skb_transport_offset (struct sk_buff const*) ; 
 int tcp_hdrlen (struct sk_buff const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int get_real_size(const struct sk_buff *skb,
			 const struct skb_shared_info *shinfo,
			 struct net_device *dev,
			 int *lso_header_size,
			 bool *inline_ok,
			 void **pfrag)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int real_size;

	if (shinfo->gso_size) {
		*inline_ok = false;
		if (skb->encapsulation)
			*lso_header_size = (skb_inner_transport_header(skb) - skb->data) + inner_tcp_hdrlen(skb);
		else
			*lso_header_size = skb_transport_offset(skb) + tcp_hdrlen(skb);
		real_size = CTRL_SIZE + shinfo->nr_frags * DS_SIZE +
			ALIGN(*lso_header_size + 4, DS_SIZE);
		if (unlikely(*lso_header_size != skb_headlen(skb))) {
			/* We add a segment for the skb linear buffer only if
			 * it contains data */
			if (*lso_header_size < skb_headlen(skb))
				real_size += DS_SIZE;
			else {
				if (netif_msg_tx_err(priv))
					en_warn(priv, "Non-linear headers\n");
				return 0;
			}
		}
	} else {
		*lso_header_size = 0;
		*inline_ok = is_inline(priv->prof->inline_thold, skb,
				       shinfo, pfrag);

		if (*inline_ok)
			real_size = inline_size(skb);
		else
			real_size = CTRL_SIZE +
				    (shinfo->nr_frags + 1) * DS_SIZE;
	}

	return real_size;
}