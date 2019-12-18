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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_handle; int /*<<< orphan*/  mc_io; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DPNI_IRQ_EVENT_ENDPOINT_CHANGED ; 
 int DPNI_IRQ_EVENT_LINK_CHANGED ; 
 int /*<<< orphan*/  DPNI_IRQ_INDEX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int dpni_get_irq_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  link_state_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_mac_addr (int /*<<< orphan*/ ) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t dpni_irq0_handler_thread(int irq_num, void *arg)
{
	u32 status = ~0;
	struct device *dev = (struct device *)arg;
	struct fsl_mc_device *dpni_dev = to_fsl_mc_device(dev);
	struct net_device *net_dev = dev_get_drvdata(dev);
	int err;

	err = dpni_get_irq_status(dpni_dev->mc_io, 0, dpni_dev->mc_handle,
				  DPNI_IRQ_INDEX, &status);
	if (unlikely(err)) {
		netdev_err(net_dev, "Can't get irq status (err %d)\n", err);
		return IRQ_HANDLED;
	}

	if (status & DPNI_IRQ_EVENT_LINK_CHANGED)
		link_state_update(netdev_priv(net_dev));

	if (status & DPNI_IRQ_EVENT_ENDPOINT_CHANGED)
		set_mac_addr(netdev_priv(net_dev));

	return IRQ_HANDLED;
}