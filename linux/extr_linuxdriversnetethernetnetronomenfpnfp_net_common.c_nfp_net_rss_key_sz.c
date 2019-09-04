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
struct nfp_net {int rss_hfunc; } ;

/* Variables and functions */
#define  ETH_RSS_HASH_CRC32 130 
#define  ETH_RSS_HASH_TOP 129 
#define  ETH_RSS_HASH_XOR 128 
 unsigned int NFP_NET_CFG_RSS_KEY_SZ ; 
 int /*<<< orphan*/  nn_warn (struct nfp_net*,char*,int) ; 

unsigned int nfp_net_rss_key_sz(struct nfp_net *nn)
{
	switch (nn->rss_hfunc) {
	case ETH_RSS_HASH_TOP:
		return NFP_NET_CFG_RSS_KEY_SZ;
	case ETH_RSS_HASH_XOR:
		return 0;
	case ETH_RSS_HASH_CRC32:
		return 4;
	}

	nn_warn(nn, "Unknown hash function: %u\n", nn->rss_hfunc);
	return 0;
}