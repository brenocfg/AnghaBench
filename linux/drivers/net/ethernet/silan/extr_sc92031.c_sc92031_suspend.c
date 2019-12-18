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
struct sc92031_priv {int /*<<< orphan*/  lock; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  _sc92031_disable_tx_rx (struct net_device*) ; 
 int /*<<< orphan*/  _sc92031_tx_clear (struct net_device*) ; 
 struct sc92031_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc92031_disable_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc92031_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct sc92031_priv *priv = netdev_priv(dev);

	pci_save_state(pdev);

	if (!netif_running(dev))
		goto out;

	netif_device_detach(dev);

	/* Disable interrupts, stop Tx and Rx. */
	sc92031_disable_interrupts(dev);

	spin_lock_bh(&priv->lock);

	_sc92031_disable_tx_rx(dev);
	_sc92031_tx_clear(dev);

	spin_unlock_bh(&priv->lock);

out:
	pci_set_power_state(pdev, pci_choose_state(pdev, state));

	return 0;
}