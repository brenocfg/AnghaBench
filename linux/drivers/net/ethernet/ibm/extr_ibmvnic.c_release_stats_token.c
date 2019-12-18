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
struct ibmvnic_adapter {int /*<<< orphan*/  stats_token; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_stats_token(struct ibmvnic_adapter *adapter)
{
	struct device *dev = &adapter->vdev->dev;

	if (!adapter->stats_token)
		return;

	dma_unmap_single(dev, adapter->stats_token,
			 sizeof(struct ibmvnic_statistics),
			 DMA_FROM_DEVICE);
	adapter->stats_token = 0;
}