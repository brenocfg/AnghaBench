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
struct net_device {int /*<<< orphan*/  name; } ;
struct e1000_adapter {TYPE_1__* pdev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  e1000_intr ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int e1000_request_irq(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	irq_handler_t handler = e1000_intr;
	int irq_flags = IRQF_SHARED;
	int err;

	err = request_irq(adapter->pdev->irq, handler, irq_flags, netdev->name,
			  netdev);
	if (err) {
		e_err(probe, "Unable to allocate interrupt Error: %d\n", err);
	}

	return err;
}