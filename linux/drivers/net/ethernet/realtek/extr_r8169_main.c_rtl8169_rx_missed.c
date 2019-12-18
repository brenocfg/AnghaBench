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
struct rtl8169_private {scalar_t__ mac_version; } ;
struct TYPE_2__ {int rx_missed_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RxMissed ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void rtl8169_rx_missed(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (tp->mac_version > RTL_GIGA_MAC_VER_06)
		return;

	dev->stats.rx_missed_errors += RTL_R32(tp, RxMissed) & 0xffffff;
	RTL_W32(tp, RxMissed, 0);
}