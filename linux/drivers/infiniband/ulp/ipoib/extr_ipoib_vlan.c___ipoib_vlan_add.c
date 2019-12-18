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
typedef  int u16 ;
struct net_device {scalar_t__ reg_state; int /*<<< orphan*/  (* priv_destructor ) (struct net_device*) ;int /*<<< orphan*/  dev; } ;
struct ipoib_dev_priv {int pkey; int child_type; struct net_device* dev; struct net_device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTUNIQ ; 
 int IPOIB_LEGACY_CHILD ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_attr_parent ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipoib_add_pkey_attr (struct net_device*) ; 
 scalar_t__ ipoib_add_umcast_attr (struct net_device*) ; 
 scalar_t__ ipoib_cm_add_mode_attr (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_intf_free (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int /*<<< orphan*/  is_child_unique (struct ipoib_dev_priv*,struct ipoib_dev_priv*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

int __ipoib_vlan_add(struct ipoib_dev_priv *ppriv, struct ipoib_dev_priv *priv,
		     u16 pkey, int type)
{
	struct net_device *ndev = priv->dev;
	int result;

	ASSERT_RTNL();

	/*
	 * We do not need to touch priv if register_netdevice fails, so just
	 * always use this flow.
	 */
	ndev->priv_destructor = ipoib_intf_free;

	/*
	 * Racing with unregister of the parent must be prevented by the
	 * caller.
	 */
	WARN_ON(ppriv->dev->reg_state != NETREG_REGISTERED);

	if (pkey == 0 || pkey == 0x8000) {
		result = -EINVAL;
		goto out_early;
	}

	priv->parent = ppriv->dev;
	priv->pkey = pkey;
	priv->child_type = type;

	if (!is_child_unique(ppriv, priv)) {
		result = -ENOTUNIQ;
		goto out_early;
	}

	result = register_netdevice(ndev);
	if (result) {
		ipoib_warn(priv, "failed to initialize; error %i", result);

		/*
		 * register_netdevice sometimes calls priv_destructor,
		 * sometimes not. Make sure it was done.
		 */
		goto out_early;
	}

	/* RTNL childs don't need proprietary sysfs entries */
	if (type == IPOIB_LEGACY_CHILD) {
		if (ipoib_cm_add_mode_attr(ndev))
			goto sysfs_failed;
		if (ipoib_add_pkey_attr(ndev))
			goto sysfs_failed;
		if (ipoib_add_umcast_attr(ndev))
			goto sysfs_failed;

		if (device_create_file(&ndev->dev, &dev_attr_parent))
			goto sysfs_failed;
	}

	return 0;

sysfs_failed:
	unregister_netdevice(priv->dev);
	return -ENOMEM;

out_early:
	if (ndev->priv_destructor)
		ndev->priv_destructor(ndev);
	return result;
}