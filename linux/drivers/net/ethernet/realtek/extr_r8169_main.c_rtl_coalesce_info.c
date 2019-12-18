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
struct rtl_coalesce_info {scalar_t__ speed; } ;
struct rtl8169_private {scalar_t__ mac_version; TYPE_1__* phydev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELNRNG ; 
 struct rtl_coalesce_info const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 struct rtl_coalesce_info* rtl_coalesce_info_8168_8136 ; 
 struct rtl_coalesce_info* rtl_coalesce_info_8169 ; 

__attribute__((used)) static const struct rtl_coalesce_info *rtl_coalesce_info(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	const struct rtl_coalesce_info *ci;

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		ci = rtl_coalesce_info_8169;
	else
		ci = rtl_coalesce_info_8168_8136;

	for (; ci->speed; ci++) {
		if (tp->phydev->speed == ci->speed)
			return ci;
	}

	return ERR_PTR(-ELNRNG);
}