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
struct ibmveth_adapter {int /*<<< orphan*/  napi; TYPE_1__* vdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long H_SUCCESS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  VIO_IRQ_DISABLE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 unsigned long h_vio_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t ibmveth_interrupt(int irq, void *dev_instance)
{
	struct net_device *netdev = dev_instance;
	struct ibmveth_adapter *adapter = netdev_priv(netdev);
	unsigned long lpar_rc;

	if (napi_schedule_prep(&adapter->napi)) {
		lpar_rc = h_vio_signal(adapter->vdev->unit_address,
				       VIO_IRQ_DISABLE);
		BUG_ON(lpar_rc != H_SUCCESS);
		__napi_schedule(&adapter->napi);
	}
	return IRQ_HANDLED;
}