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
struct ibmvnic_statistics {int dummy; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  stats_token; int /*<<< orphan*/  stats; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stats_token(struct ibmvnic_adapter *adapter)
{
	struct device *dev = &adapter->vdev->dev;
	dma_addr_t stok;

	stok = dma_map_single(dev, &adapter->stats,
			      sizeof(struct ibmvnic_statistics),
			      DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, stok)) {
		dev_err(dev, "Couldn't map stats buffer\n");
		return -1;
	}

	adapter->stats_token = stok;
	netdev_dbg(adapter->netdev, "Stats token initialized (%llx)\n", stok);
	return 0;
}