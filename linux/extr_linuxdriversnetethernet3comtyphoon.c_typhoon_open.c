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
struct typhoon {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  NoWait ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  TYPHOON_STATUS_WAITING_FOR_HOST ; 
 int /*<<< orphan*/  WaitSleep ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ typhoon_boot_3XP (struct typhoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_interrupt ; 
 int typhoon_request_firmware (struct typhoon*) ; 
 int /*<<< orphan*/  typhoon_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ typhoon_sleep (struct typhoon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int typhoon_start_runtime (struct typhoon*) ; 
 int typhoon_wakeup (struct typhoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
typhoon_open(struct net_device *dev)
{
	struct typhoon *tp = netdev_priv(dev);
	int err;

	err = typhoon_request_firmware(tp);
	if (err)
		goto out;

	err = typhoon_wakeup(tp, WaitSleep);
	if(err < 0) {
		netdev_err(dev, "unable to wakeup device\n");
		goto out_sleep;
	}

	err = request_irq(dev->irq, typhoon_interrupt, IRQF_SHARED,
				dev->name, dev);
	if(err < 0)
		goto out_sleep;

	napi_enable(&tp->napi);

	err = typhoon_start_runtime(tp);
	if(err < 0) {
		napi_disable(&tp->napi);
		goto out_irq;
	}

	netif_start_queue(dev);
	return 0;

out_irq:
	free_irq(dev->irq, dev);

out_sleep:
	if(typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_HOST) < 0) {
		netdev_err(dev, "unable to reboot into sleep img\n");
		typhoon_reset(tp->ioaddr, NoWait);
		goto out;
	}

	if(typhoon_sleep(tp, PCI_D3hot, 0) < 0)
		netdev_err(dev, "unable to go back to sleep\n");

out:
	return err;
}