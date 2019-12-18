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
struct usbnet {int dummy; } ;
struct rndis_wlan_private {int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  work_pending; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_SET_MULTICAST_LIST ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rndis_wlan_set_multicast_list(struct net_device *dev)
{
	struct usbnet *usbdev = netdev_priv(dev);
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);

	if (test_bit(WORK_SET_MULTICAST_LIST, &priv->work_pending))
		return;

	set_bit(WORK_SET_MULTICAST_LIST, &priv->work_pending);
	queue_work(priv->workqueue, &priv->work);
}