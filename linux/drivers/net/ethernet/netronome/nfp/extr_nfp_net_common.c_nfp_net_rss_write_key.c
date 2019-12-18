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
struct nfp_net {scalar_t__ rss_key; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_RSS_KEY ; 
 int /*<<< orphan*/  get_unaligned_le32 (scalar_t__) ; 
 int nfp_net_rss_key_sz (struct nfp_net*) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,scalar_t__,int /*<<< orphan*/ ) ; 

void nfp_net_rss_write_key(struct nfp_net *nn)
{
	int i;

	for (i = 0; i < nfp_net_rss_key_sz(nn); i += 4)
		nn_writel(nn, NFP_NET_CFG_RSS_KEY + i,
			  get_unaligned_le32(nn->rss_key + i));
}