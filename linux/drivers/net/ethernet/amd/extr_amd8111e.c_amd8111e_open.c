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
struct net_device {scalar_t__ irq; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipg_timer; } ;
struct amd8111e_priv {int options; int opened; int /*<<< orphan*/  lock; TYPE_1__ ipg_data; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int OPTION_DYN_IPG_ENABLE ; 
 int /*<<< orphan*/  add_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amd8111e_init_hw_default (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  amd8111e_interrupt ; 
 scalar_t__ amd8111e_restart (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd8111e_open(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);

	if(dev->irq ==0 || request_irq(dev->irq, amd8111e_interrupt, IRQF_SHARED,
					 dev->name, dev))
		return -EAGAIN;

	napi_enable(&lp->napi);

	spin_lock_irq(&lp->lock);

	amd8111e_init_hw_default(lp);

	if(amd8111e_restart(dev)){
		spin_unlock_irq(&lp->lock);
		napi_disable(&lp->napi);
		if (dev->irq)
			free_irq(dev->irq, dev);
		return -ENOMEM;
	}
	/* Start ipg timer */
	if(lp->options & OPTION_DYN_IPG_ENABLE){
		add_timer(&lp->ipg_data.ipg_timer);
		netdev_info(dev, "Dynamic IPG Enabled\n");
	}

	lp->opened = 1;

	spin_unlock_irq(&lp->lock);

	netif_start_queue(dev);

	return 0;
}