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
struct net_device {scalar_t__ reg_state; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  ca; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  intf_name ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EPERM ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IPOIB_LEGACY_CHILD ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 scalar_t__ NETREG_REGISTERED ; 
 scalar_t__ NETREG_UNINITIALIZED ; 
 int PTR_ERR (struct net_device*) ; 
 int __ipoib_vlan_add (struct ipoib_dev_priv*,struct ipoib_dev_priv*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device* ipoib_intf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int restart_syscall () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,unsigned short) ; 

int ipoib_vlan_add(struct net_device *pdev, unsigned short pkey)
{
	struct ipoib_dev_priv *ppriv, *priv;
	char intf_name[IFNAMSIZ];
	struct net_device *ndev;
	int result;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (!rtnl_trylock())
		return restart_syscall();

	if (pdev->reg_state != NETREG_REGISTERED) {
		rtnl_unlock();
		return -EPERM;
	}

	ppriv = ipoib_priv(pdev);

	snprintf(intf_name, sizeof(intf_name), "%s.%04x",
		 ppriv->dev->name, pkey);

	ndev = ipoib_intf_alloc(ppriv->ca, ppriv->port, intf_name);
	if (IS_ERR(ndev)) {
		result = PTR_ERR(ndev);
		goto out;
	}
	priv = ipoib_priv(ndev);

	result = __ipoib_vlan_add(ppriv, priv, pkey, IPOIB_LEGACY_CHILD);

	if (result && ndev->reg_state == NETREG_UNINITIALIZED)
		free_netdev(ndev);

out:
	rtnl_unlock();

	return result;
}