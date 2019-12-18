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
struct rtl8169_private {int /*<<< orphan*/  phydev; TYPE_1__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ net_ratelimit () ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_request_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_link_chg_patch (struct rtl8169_private*) ; 

__attribute__((used)) static void r8169_phylink_handler(struct net_device *ndev)
{
	struct rtl8169_private *tp = netdev_priv(ndev);

	if (netif_carrier_ok(ndev)) {
		rtl_link_chg_patch(tp);
		pm_request_resume(&tp->pci_dev->dev);
	} else {
		pm_runtime_idle(&tp->pci_dev->dev);
	}

	if (net_ratelimit())
		phy_print_status(tp->phydev);
}