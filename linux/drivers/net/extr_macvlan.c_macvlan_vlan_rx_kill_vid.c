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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct macvlan_dev {struct net_device* lowerdev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vlan_vid_del (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macvlan_vlan_rx_kill_vid(struct net_device *dev,
				    __be16 proto, u16 vid)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	vlan_vid_del(lowerdev, proto, vid);
	return 0;
}