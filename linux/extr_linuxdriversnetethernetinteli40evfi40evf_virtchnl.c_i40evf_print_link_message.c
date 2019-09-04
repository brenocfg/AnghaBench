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
struct net_device {int dummy; } ;
struct i40evf_adapter {int link_speed; int /*<<< orphan*/  link_up; struct net_device* netdev; } ;

/* Variables and functions */
#define  I40E_LINK_SPEED_100MB 133 
#define  I40E_LINK_SPEED_10GB 132 
#define  I40E_LINK_SPEED_1GB 131 
#define  I40E_LINK_SPEED_20GB 130 
#define  I40E_LINK_SPEED_25GB 129 
#define  I40E_LINK_SPEED_40GB 128 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 

__attribute__((used)) static void i40evf_print_link_message(struct i40evf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	char *speed = "Unknown ";

	if (!adapter->link_up) {
		netdev_info(netdev, "NIC Link is Down\n");
		return;
	}

	switch (adapter->link_speed) {
	case I40E_LINK_SPEED_40GB:
		speed = "40 G";
		break;
	case I40E_LINK_SPEED_25GB:
		speed = "25 G";
		break;
	case I40E_LINK_SPEED_20GB:
		speed = "20 G";
		break;
	case I40E_LINK_SPEED_10GB:
		speed = "10 G";
		break;
	case I40E_LINK_SPEED_1GB:
		speed = "1000 M";
		break;
	case I40E_LINK_SPEED_100MB:
		speed = "100 M";
		break;
	default:
		break;
	}

	netdev_info(netdev, "NIC Link is Up %sbps Full Duplex\n", speed);
}