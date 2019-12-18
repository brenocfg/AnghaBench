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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct rtl8169_private {TYPE_1__ wk; int /*<<< orphan*/  napi; int /*<<< orphan*/  phydev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL_FLAG_MAX ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_pll_power_down (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_net_suspend(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (!netif_running(dev))
		return;

	phy_stop(tp->phydev);
	netif_device_detach(dev);

	rtl_lock_work(tp);
	napi_disable(&tp->napi);
	/* Clear all task flags */
	bitmap_zero(tp->wk.flags, RTL_FLAG_MAX);

	rtl_unlock_work(tp);

	rtl_pll_power_down(tp);
}