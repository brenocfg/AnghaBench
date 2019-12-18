#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct ipw2100_priv {TYPE_4__* ieee; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  action_mutex; int /*<<< orphan*/  status; struct net_device* net_dev; } ;
struct TYPE_11__ {scalar_t__ version; } ;
struct TYPE_9__ {int /*<<< orphan*/  channels; } ;
struct TYPE_8__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_10__ {TYPE_3__ bg_band; TYPE_2__ wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  STATUS_INITIALIZED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ipw2100_priv*) ; 
 int /*<<< orphan*/  free_libipw (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw2100_attribute_group ; 
 int /*<<< orphan*/  ipw2100_down (struct ipw2100_priv*) ; 
 TYPE_5__ ipw2100_firmware ; 
 int /*<<< orphan*/  ipw2100_kill_works (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_queues_free (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_release_firmware (struct ipw2100_priv*,TYPE_5__*) ; 
 int /*<<< orphan*/  ipw2100_snapshot_free (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ipw2100_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw2100_pci_remove_one(struct pci_dev *pci_dev)
{
	struct ipw2100_priv *priv = pci_get_drvdata(pci_dev);
	struct net_device *dev = priv->net_dev;

	mutex_lock(&priv->action_mutex);

	priv->status &= ~STATUS_INITIALIZED;

	sysfs_remove_group(&pci_dev->dev.kobj, &ipw2100_attribute_group);

#ifdef CONFIG_PM
	if (ipw2100_firmware.version)
		ipw2100_release_firmware(priv, &ipw2100_firmware);
#endif
	/* Take down the hardware */
	ipw2100_down(priv);

	/* Release the mutex so that the network subsystem can
	 * complete any needed calls into the driver... */
	mutex_unlock(&priv->action_mutex);

	/* Unregister the device first - this results in close()
	 * being called if the device is open.  If we free storage
	 * first, then close() will crash.
	 * FIXME: remove the comment above. */
	unregister_netdev(dev);

	ipw2100_kill_works(priv);

	ipw2100_queues_free(priv);

	/* Free potential debugging firmware snapshot */
	ipw2100_snapshot_free(priv);

	free_irq(dev->irq, priv);

	pci_iounmap(pci_dev, priv->ioaddr);

	/* wiphy_unregister needs to be here, before free_libipw */
	wiphy_unregister(priv->ieee->wdev.wiphy);
	kfree(priv->ieee->bg_band.channels);
	free_libipw(dev, 0);

	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);

	IPW_DEBUG_INFO("exit\n");
}