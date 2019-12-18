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
struct ibmvnic_long_term_buff {int /*<<< orphan*/  addr; int /*<<< orphan*/  buff; int /*<<< orphan*/  size; int /*<<< orphan*/  map_id; } ;
struct ibmvnic_adapter {scalar_t__ reset_reason; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ VNIC_RESET_FAILOVER ; 
 scalar_t__ VNIC_RESET_MOBILITY ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_unmap (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_long_term_buff(struct ibmvnic_adapter *adapter,
				struct ibmvnic_long_term_buff *ltb)
{
	struct device *dev = &adapter->vdev->dev;

	if (!ltb->buff)
		return;

	if (adapter->reset_reason != VNIC_RESET_FAILOVER &&
	    adapter->reset_reason != VNIC_RESET_MOBILITY)
		send_request_unmap(adapter, ltb->map_id);
	dma_free_coherent(dev, ltb->size, ltb->buff, ltb->addr);
}