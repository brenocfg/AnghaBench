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
struct net_device {int dummy; } ;
struct et131x_adapter {int /*<<< orphan*/  error_timer; TYPE_1__* pdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMP_ADAPTER_INTERRUPT_IN_USE ; 
 int del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et131x_down (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int et131x_close(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);

	et131x_down(netdev);
	napi_disable(&adapter->napi);

	adapter->flags &= ~FMP_ADAPTER_INTERRUPT_IN_USE;
	free_irq(adapter->pdev->irq, netdev);

	/* Stop the error timer */
	return del_timer_sync(&adapter->error_timer);
}