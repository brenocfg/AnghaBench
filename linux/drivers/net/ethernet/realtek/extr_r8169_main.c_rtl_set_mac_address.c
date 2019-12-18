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
struct rtl8169_private {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int eth_mac_addr (struct net_device*,void*) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 scalar_t__ pm_runtime_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  rtl_rar_set (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl_set_mac_address(struct net_device *dev, void *p)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct device *d = tp_to_dev(tp);
	int ret;

	ret = eth_mac_addr(dev, p);
	if (ret)
		return ret;

	pm_runtime_get_noresume(d);

	if (pm_runtime_active(d))
		rtl_rar_set(tp, dev->dev_addr);

	pm_runtime_put_noidle(d);

	return 0;
}