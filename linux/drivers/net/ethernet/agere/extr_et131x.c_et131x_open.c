#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {unsigned int irq; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct et131x_adapter {int /*<<< orphan*/  napi; int /*<<< orphan*/  flags; TYPE_1__ error_timer; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TX_ERROR_PERIOD ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  et131x_error_timer_handler ; 
 int /*<<< orphan*/  et131x_isr ; 
 int /*<<< orphan*/  et131x_up (struct net_device*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int et131x_open(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;
	unsigned int irq = pdev->irq;
	int result;

	/* Start the timer to track NIC errors */
	timer_setup(&adapter->error_timer, et131x_error_timer_handler, 0);
	adapter->error_timer.expires = jiffies +
		msecs_to_jiffies(TX_ERROR_PERIOD);
	add_timer(&adapter->error_timer);

	result = request_irq(irq, et131x_isr,
			     IRQF_SHARED, netdev->name, netdev);
	if (result) {
		dev_err(&pdev->dev, "could not register IRQ %d\n", irq);
		return result;
	}

	adapter->flags |= FMP_ADAPTER_INTERRUPT_IN_USE;

	napi_enable(&adapter->napi);

	et131x_up(netdev);

	return result;
}