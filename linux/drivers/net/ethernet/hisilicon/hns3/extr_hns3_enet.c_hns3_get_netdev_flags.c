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
typedef  int u8 ;
struct net_device {int flags; } ;

/* Variables and functions */
 int HNAE3_BPE ; 
 int HNAE3_USER_MPE ; 
 int HNAE3_USER_UPE ; 
 int HNAE3_VLAN_FLTR ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 

__attribute__((used)) static u8 hns3_get_netdev_flags(struct net_device *netdev)
{
	u8 flags = 0;

	if (netdev->flags & IFF_PROMISC) {
		flags = HNAE3_USER_UPE | HNAE3_USER_MPE | HNAE3_BPE;
	} else {
		flags |= HNAE3_VLAN_FLTR;
		if (netdev->flags & IFF_ALLMULTI)
			flags |= HNAE3_USER_MPE;
	}

	return flags;
}