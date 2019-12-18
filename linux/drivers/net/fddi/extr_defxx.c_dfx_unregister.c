#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  mem; } ;
struct TYPE_5__ {int rcv_bufs_to_post; TYPE_1__ base; int /*<<< orphan*/  kmalloced_dma; scalar_t__ kmalloced; } ;
typedef  int /*<<< orphan*/  PI_DESCR_BLOCK ;
typedef  int /*<<< orphan*/  PI_CONSUMER_BLOCK ;
typedef  TYPE_2__ DFX_board_t ;

/* Variables and functions */
 int DFX_BUS_TC (struct device*) ; 
 scalar_t__ DFX_MMIO ; 
 int PI_ALIGN_K_DESC_BLK ; 
 int PI_CMD_REQ_K_SIZE_MAX ; 
 int PI_CMD_RSP_K_SIZE_MAX ; 
 int PI_RCV_DATA_K_SIZE_MAX ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dfx_bus_uninit (struct net_device*) ; 
 int /*<<< orphan*/  dfx_get_bars (struct device*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void dfx_unregister(struct device *bdev)
{
	struct net_device *dev = dev_get_drvdata(bdev);
	DFX_board_t *bp = netdev_priv(dev);
	int dfx_bus_pci = dev_is_pci(bdev);
	int dfx_bus_tc = DFX_BUS_TC(bdev);
	int dfx_use_mmio = DFX_MMIO || dfx_bus_tc;
	resource_size_t bar_start[3] = {0};	/* pointers to ports */
	resource_size_t bar_len[3] = {0};	/* resource lengths */
	int		alloc_size;		/* total buffer size used */

	unregister_netdev(dev);

	alloc_size = sizeof(PI_DESCR_BLOCK) +
		     PI_CMD_REQ_K_SIZE_MAX + PI_CMD_RSP_K_SIZE_MAX +
#ifndef DYNAMIC_BUFFERS
		     (bp->rcv_bufs_to_post * PI_RCV_DATA_K_SIZE_MAX) +
#endif
		     sizeof(PI_CONSUMER_BLOCK) +
		     (PI_ALIGN_K_DESC_BLK - 1);
	if (bp->kmalloced)
		dma_free_coherent(bdev, alloc_size,
				  bp->kmalloced, bp->kmalloced_dma);

	dfx_bus_uninit(dev);

	dfx_get_bars(bdev, bar_start, bar_len);
	if (bar_start[2] != 0)
		release_region(bar_start[2], bar_len[2]);
	if (bar_start[1] != 0)
		release_region(bar_start[1], bar_len[1]);
	if (dfx_use_mmio) {
		iounmap(bp->base.mem);
		release_mem_region(bar_start[0], bar_len[0]);
	} else
		release_region(bar_start[0], bar_len[0]);

	if (dfx_bus_pci)
		pci_disable_device(to_pci_dev(bdev));

	free_netdev(dev);
}