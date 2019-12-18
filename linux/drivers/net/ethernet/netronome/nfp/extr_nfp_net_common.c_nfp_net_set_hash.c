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
struct nfp_meta_parsed {int /*<<< orphan*/  hash; int /*<<< orphan*/  hash_type; } ;
struct net_device {int features; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NETIF_F_RXHASH ; 
#define  NFP_NET_RSS_IPV4 130 
#define  NFP_NET_RSS_IPV6 129 
#define  NFP_NET_RSS_IPV6_EX 128 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 int /*<<< orphan*/  get_unaligned_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfp_net_set_hash(struct net_device *netdev, struct nfp_meta_parsed *meta,
		 unsigned int type, __be32 *hash)
{
	if (!(netdev->features & NETIF_F_RXHASH))
		return;

	switch (type) {
	case NFP_NET_RSS_IPV4:
	case NFP_NET_RSS_IPV6:
	case NFP_NET_RSS_IPV6_EX:
		meta->hash_type = PKT_HASH_TYPE_L3;
		break;
	default:
		meta->hash_type = PKT_HASH_TYPE_L4;
		break;
	}

	meta->hash = get_unaligned_be32(hash);
}