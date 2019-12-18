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
struct rtl8139_private {scalar_t__* phys; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 struct rtl8139_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_link (struct rtl8139_private*) ; 

__attribute__((used)) static void rtl_check_media (struct net_device *dev, unsigned int init_media)
{
	struct rtl8139_private *tp = netdev_priv(dev);

	if (tp->phys[0] >= 0) {
		mii_check_media(&tp->mii, netif_msg_link(tp), init_media);
	}
}