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
struct wireless_dev {struct net_device* netdev; int /*<<< orphan*/  iftype; } ;
struct net_device {int watchdog_timeo; int flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; struct lbs_private* ml_priv; struct wireless_dev* ieee80211_ptr; } ;
struct lbs_private {int wol_gpio; int wol_gap; int ehs_remove_supported; int /*<<< orphan*/  wol_criteria; int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  work_thread; struct wireless_dev* main_thread; int /*<<< orphan*/  waitq; void* card; struct net_device* dev; struct wireless_dev* wdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHS_REMOVE_WAKEUP ; 
 int ENOMEM ; 
 struct lbs_private* ERR_PTR (int) ; 
 int HZ ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct wireless_dev*) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int PTR_ERR (struct wireless_dev*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct wireless_dev* kthread_run (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 struct wireless_dev* lbs_cfg_alloc (struct device*) ; 
 int /*<<< orphan*/  lbs_cfg_free (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_thread (char*) ; 
 int /*<<< orphan*/  lbs_ethtool_ops ; 
 int /*<<< orphan*/  lbs_free_adapter (struct lbs_private*) ; 
 int lbs_init_adapter (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_netdev_ops ; 
 int /*<<< orphan*/  lbs_set_mcast_worker ; 
 int /*<<< orphan*/  lbs_thread ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct lbs_private* wdev_priv (struct wireless_dev*) ; 

struct lbs_private *lbs_add_card(void *card, struct device *dmdev)
{
	struct net_device *dev;
	struct wireless_dev *wdev;
	struct lbs_private *priv = NULL;
	int err;

	/* Allocate an Ethernet device and register it */
	wdev = lbs_cfg_alloc(dmdev);
	if (IS_ERR(wdev)) {
		err = PTR_ERR(wdev);
		pr_err("cfg80211 init failed\n");
		goto err_cfg;
	}

	wdev->iftype = NL80211_IFTYPE_STATION;
	priv = wdev_priv(wdev);
	priv->wdev = wdev;

	err = lbs_init_adapter(priv);
	if (err) {
		pr_err("failed to initialize adapter structure\n");
		goto err_wdev;
	}

	dev = alloc_netdev(0, "wlan%d", NET_NAME_UNKNOWN, ether_setup);
	if (!dev) {
		err = -ENOMEM;
		dev_err(dmdev, "no memory for network device instance\n");
		goto err_adapter;
	}

	dev->ieee80211_ptr = wdev;
	dev->ml_priv = priv;
	SET_NETDEV_DEV(dev, dmdev);
	wdev->netdev = dev;
	priv->dev = dev;

 	dev->netdev_ops = &lbs_netdev_ops;
	dev->watchdog_timeo = 5 * HZ;
	dev->ethtool_ops = &lbs_ethtool_ops;
	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;

	priv->card = card;

	strcpy(dev->name, "wlan%d");

	lbs_deb_thread("Starting main thread...\n");
	init_waitqueue_head(&priv->waitq);
	priv->main_thread = kthread_run(lbs_thread, dev, "lbs_main");
	if (IS_ERR(priv->main_thread)) {
		err = PTR_ERR(priv->main_thread);
		lbs_deb_thread("Error creating main thread.\n");
		goto err_ndev;
	}

	priv->work_thread = create_singlethread_workqueue("lbs_worker");
	INIT_WORK(&priv->mcast_work, lbs_set_mcast_worker);

	priv->wol_criteria = EHS_REMOVE_WAKEUP;
	priv->wol_gpio = 0xff;
	priv->wol_gap = 20;
	priv->ehs_remove_supported = true;

	return priv;

 err_ndev:
	free_netdev(dev);

 err_adapter:
	lbs_free_adapter(priv);

 err_wdev:
	lbs_cfg_free(priv);

 err_cfg:
	return ERR_PTR(err);
}