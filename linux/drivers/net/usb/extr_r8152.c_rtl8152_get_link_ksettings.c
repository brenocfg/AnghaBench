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
struct TYPE_2__ {int /*<<< orphan*/  mdio_read; } ;
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; TYPE_1__ mii; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (TYPE_1__*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int rtl8152_get_link_ksettings(struct net_device *netdev,
			       struct ethtool_link_ksettings *cmd)
{
	struct r8152 *tp = netdev_priv(netdev);
	int ret;

	if (!tp->mii.mdio_read)
		return -EOPNOTSUPP;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	mii_ethtool_get_link_ksettings(&tp->mii, cmd);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}