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
struct nfp_net_dp {int /*<<< orphan*/  rx_dma_dir; scalar_t__ fl_bufsz; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int NFP_NET_RX_BUF_HEADROOM ; 
 scalar_t__ NFP_NET_RX_BUF_NON_DATA ; 
 int /*<<< orphan*/  dma_map_single_attrs (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_addr_t nfp_net_dma_map_rx(struct nfp_net_dp *dp, void *frag)
{
	return dma_map_single_attrs(dp->dev, frag + NFP_NET_RX_BUF_HEADROOM,
				    dp->fl_bufsz - NFP_NET_RX_BUF_NON_DATA,
				    dp->rx_dma_dir, DMA_ATTR_SKIP_CPU_SYNC);
}