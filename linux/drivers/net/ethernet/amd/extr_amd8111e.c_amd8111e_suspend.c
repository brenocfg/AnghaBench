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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipg_timer; } ;
struct amd8111e_priv {int options; int /*<<< orphan*/  lock; TYPE_1__ ipg_data; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int OPTION_DYN_IPG_ENABLE ; 
 int OPTION_WAKE_MAGIC_ENABLE ; 
 int OPTION_WAKE_PHY_ENABLE ; 
 int OPTION_WOL_ENABLE ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  amd8111e_disable_interrupt (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  amd8111e_enable_link_change (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  amd8111e_enable_magicpkt (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  amd8111e_stop_chip (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd8111e_suspend(struct pci_dev *pci_dev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pci_dev);
	struct amd8111e_priv *lp = netdev_priv(dev);

	if (!netif_running(dev))
		return 0;

	/* disable the interrupt */
	spin_lock_irq(&lp->lock);
	amd8111e_disable_interrupt(lp);
	spin_unlock_irq(&lp->lock);

	netif_device_detach(dev);

	/* stop chip */
	spin_lock_irq(&lp->lock);
	if(lp->options & OPTION_DYN_IPG_ENABLE)
		del_timer_sync(&lp->ipg_data.ipg_timer);
	amd8111e_stop_chip(lp);
	spin_unlock_irq(&lp->lock);

	if(lp->options & OPTION_WOL_ENABLE){
		 /* enable wol */
		if(lp->options & OPTION_WAKE_MAGIC_ENABLE)
			amd8111e_enable_magicpkt(lp);
		if(lp->options & OPTION_WAKE_PHY_ENABLE)
			amd8111e_enable_link_change(lp);

		pci_enable_wake(pci_dev, PCI_D3hot, 1);
		pci_enable_wake(pci_dev, PCI_D3cold, 1);

	}
	else{
		pci_enable_wake(pci_dev, PCI_D3hot, 0);
		pci_enable_wake(pci_dev, PCI_D3cold, 0);
	}

	pci_save_state(pci_dev);
	pci_set_power_state(pci_dev, PCI_D3hot);

	return 0;
}