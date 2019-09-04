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
struct net_device {int flags; int mtu; } ;

/* Variables and functions */
 int CANFD_MTU ; 
 int CAN_MTU ; 
 int EBUSY ; 
 int EINVAL ; 
 int IFF_UP ; 

__attribute__((used)) static int vcan_change_mtu(struct net_device *dev, int new_mtu)
{
	/* Do not allow changing the MTU while running */
	if (dev->flags & IFF_UP)
		return -EBUSY;

	if (new_mtu != CAN_MTU && new_mtu != CANFD_MTU)
		return -EINVAL;

	dev->mtu = new_mtu;
	return 0;
}