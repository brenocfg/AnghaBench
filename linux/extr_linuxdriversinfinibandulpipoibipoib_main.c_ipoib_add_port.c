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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* priv_destructor ) (struct net_device*) ;} ;
struct ipoib_dev_priv {int /*<<< orphan*/  flush_heavy; int /*<<< orphan*/  event_handler; int /*<<< orphan*/  ca; struct net_device* dev; } ;
struct ib_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct net_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_create_child ; 
 int /*<<< orphan*/  dev_attr_delete_child ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ib_register_event_handler (int /*<<< orphan*/ *) ; 
 scalar_t__ ipoib_add_pkey_attr (struct net_device*) ; 
 scalar_t__ ipoib_add_umcast_attr (struct net_device*) ; 
 scalar_t__ ipoib_cm_add_mode_attr (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_event ; 
 struct ipoib_dev_priv* ipoib_intf_alloc (struct ib_device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ipoib_intf_free (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_parent_unregister_pre (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static struct net_device *ipoib_add_port(const char *format,
					 struct ib_device *hca, u8 port)
{
	struct ipoib_dev_priv *priv;
	struct net_device *ndev;
	int result;

	priv = ipoib_intf_alloc(hca, port, format);
	if (!priv) {
		pr_warn("%s, %d: ipoib_intf_alloc failed\n", hca->name, port);
		return ERR_PTR(-ENOMEM);
	}
	ndev = priv->dev;

	INIT_IB_EVENT_HANDLER(&priv->event_handler,
			      priv->ca, ipoib_event);
	ib_register_event_handler(&priv->event_handler);

	/* call event handler to ensure pkey in sync */
	queue_work(ipoib_workqueue, &priv->flush_heavy);

	result = register_netdev(ndev);
	if (result) {
		pr_warn("%s: couldn't register ipoib port %d; error %d\n",
			hca->name, port, result);

		ipoib_parent_unregister_pre(ndev);
		ipoib_intf_free(ndev);
		free_netdev(ndev);

		return ERR_PTR(result);
	}

	/*
	 * We cannot set priv_destructor before register_netdev because we
	 * need priv to be always valid during the error flow to execute
	 * ipoib_parent_unregister_pre(). Instead handle it manually and only
	 * enter priv_destructor mode once we are completely registered.
	 */
	ndev->priv_destructor = ipoib_intf_free;

	if (ipoib_cm_add_mode_attr(ndev))
		goto sysfs_failed;
	if (ipoib_add_pkey_attr(ndev))
		goto sysfs_failed;
	if (ipoib_add_umcast_attr(ndev))
		goto sysfs_failed;
	if (device_create_file(&ndev->dev, &dev_attr_create_child))
		goto sysfs_failed;
	if (device_create_file(&ndev->dev, &dev_attr_delete_child))
		goto sysfs_failed;

	return ndev;

sysfs_failed:
	ipoib_parent_unregister_pre(ndev);
	unregister_netdev(ndev);
	return ERR_PTR(-ENOMEM);
}