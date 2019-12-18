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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  dev_irq_num; int /*<<< orphan*/  gpio_irq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isr_bh_routine ; 
 int /*<<< orphan*/  isr_uh_routine ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct net_device*) ; 

__attribute__((used)) static int init_irq(struct net_device *dev)
{
	int ret = 0;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;

	ret = gpiod_direction_input(wl->gpio_irq);
	if (ret) {
		netdev_err(dev, "could not obtain gpio for WILC_INTR\n");
		return ret;
	}

	wl->dev_irq_num = gpiod_to_irq(wl->gpio_irq);

	ret = request_threaded_irq(wl->dev_irq_num, isr_uh_routine,
				   isr_bh_routine,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "WILC_IRQ", dev);
	if (ret < 0)
		netdev_err(dev, "Failed to request IRQ\n");
	else
		netdev_dbg(dev, "IRQ request succeeded IRQ-NUM= %d\n",
			   wl->dev_irq_num);

	return ret;
}