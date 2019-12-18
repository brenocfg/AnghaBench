#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int features; } ;
struct cqe_rx_t {int rss_alg; int /*<<< orphan*/  rss_tag; } ;

/* Variables and functions */
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_NONE ; 
#define  RSS_ALG_IP 130 
#define  RSS_ALG_TCP_IP 129 
#define  RSS_ALG_UDP_IP 128 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nicvf_set_rxhash(struct net_device *netdev,
				    struct cqe_rx_t *cqe_rx,
				    struct sk_buff *skb)
{
	u8 hash_type;
	u32 hash;

	if (!(netdev->features & NETIF_F_RXHASH))
		return;

	switch (cqe_rx->rss_alg) {
	case RSS_ALG_TCP_IP:
	case RSS_ALG_UDP_IP:
		hash_type = PKT_HASH_TYPE_L4;
		hash = cqe_rx->rss_tag;
		break;
	case RSS_ALG_IP:
		hash_type = PKT_HASH_TYPE_L3;
		hash = cqe_rx->rss_tag;
		break;
	default:
		hash_type = PKT_HASH_TYPE_NONE;
		hash = 0;
	}

	skb_set_hash(skb, hash, hash_type);
}