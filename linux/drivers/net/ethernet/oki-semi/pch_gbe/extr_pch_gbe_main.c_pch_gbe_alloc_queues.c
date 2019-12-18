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
struct pch_gbe_adapter {void* rx_ring; TYPE_1__* pdev; void* tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pch_gbe_alloc_queues(struct pch_gbe_adapter *adapter)
{
	adapter->tx_ring = devm_kzalloc(&adapter->pdev->dev,
					sizeof(*adapter->tx_ring), GFP_KERNEL);
	if (!adapter->tx_ring)
		return -ENOMEM;

	adapter->rx_ring = devm_kzalloc(&adapter->pdev->dev,
					sizeof(*adapter->rx_ring), GFP_KERNEL);
	if (!adapter->rx_ring)
		return -ENOMEM;
	return 0;
}