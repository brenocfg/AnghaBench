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
struct nfp_net_dp {int /*<<< orphan*/  rx_dma_dir; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ NFP_NET_RX_BUF_HEADROOM ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_dma_sync_cpu_rx(struct nfp_net_dp *dp, dma_addr_t dma_addr,
				    unsigned int len)
{
	dma_sync_single_for_cpu(dp->dev, dma_addr - NFP_NET_RX_BUF_HEADROOM,
				len, dp->rx_dma_dir);
}