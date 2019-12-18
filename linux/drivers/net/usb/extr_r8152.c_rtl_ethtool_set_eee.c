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
struct TYPE_2__ {int (* eee_set ) (struct r8152*,struct ethtool_eee*) ;} ;
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; int /*<<< orphan*/  mii; TYPE_1__ rtl_ops; } ;
struct net_device {int dummy; } ;
struct ethtool_eee {int dummy; } ;

/* Variables and functions */
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int stub1 (struct r8152*,struct ethtool_eee*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtl_ethtool_set_eee(struct net_device *net, struct ethtool_eee *edata)
{
	struct r8152 *tp = netdev_priv(net);
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	ret = tp->rtl_ops.eee_set(tp, edata);
	if (!ret)
		ret = mii_nway_restart(&tp->mii);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}