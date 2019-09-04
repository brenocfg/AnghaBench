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
 scalar_t__ NFP_NET_RX_BUF_NON_DATA ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_dma_sync_dev_rx(const struct nfp_net_dp *dp, dma_addr_t dma_addr)
{
	dma_sync_single_for_device(dp->dev, dma_addr,
				   dp->fl_bufsz - NFP_NET_RX_BUF_NON_DATA,
				   dp->rx_dma_dir);
}