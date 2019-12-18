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
struct skb_shared_info {int dummy; } ;
struct nfp_net_dp {scalar_t__ rx_offset; scalar_t__ mtu; scalar_t__ rx_dma_off; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ NFP_NET_CFG_RX_OFFSET_DYNAMIC ; 
 scalar_t__ NFP_NET_MAX_PREPEND ; 
 unsigned int NFP_NET_RX_BUF_HEADROOM ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 int VLAN_HLEN ; 

__attribute__((used)) static unsigned int
nfp_net_calc_fl_bufsz(struct nfp_net_dp *dp)
{
	unsigned int fl_bufsz;

	fl_bufsz = NFP_NET_RX_BUF_HEADROOM;
	fl_bufsz += dp->rx_dma_off;
	if (dp->rx_offset == NFP_NET_CFG_RX_OFFSET_DYNAMIC)
		fl_bufsz += NFP_NET_MAX_PREPEND;
	else
		fl_bufsz += dp->rx_offset;
	fl_bufsz += ETH_HLEN + VLAN_HLEN * 2 + dp->mtu;

	fl_bufsz = SKB_DATA_ALIGN(fl_bufsz);
	fl_bufsz += SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	return fl_bufsz;
}