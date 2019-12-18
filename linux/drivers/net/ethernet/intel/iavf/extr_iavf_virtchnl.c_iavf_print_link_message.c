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
struct iavf_adapter {int link_speed; int /*<<< orphan*/  link_up; struct net_device* netdev; } ;

/* Variables and functions */
#define  IAVF_LINK_SPEED_100MB 133 
#define  IAVF_LINK_SPEED_10GB 132 
#define  IAVF_LINK_SPEED_1GB 131 
#define  IAVF_LINK_SPEED_20GB 130 
#define  IAVF_LINK_SPEED_25GB 129 
#define  IAVF_LINK_SPEED_40GB 128 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 

__attribute__((used)) static void iavf_print_link_message(struct iavf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	char *speed = "Unknown ";

	if (!adapter->link_up) {
		netdev_info(netdev, "NIC Link is Down\n");
		return;
	}

	switch (adapter->link_speed) {
	case IAVF_LINK_SPEED_40GB:
		speed = "40 G";
		break;
	case IAVF_LINK_SPEED_25GB:
		speed = "25 G";
		break;
	case IAVF_LINK_SPEED_20GB:
		speed = "20 G";
		break;
	case IAVF_LINK_SPEED_10GB:
		speed = "10 G";
		break;
	case IAVF_LINK_SPEED_1GB:
		speed = "1000 M";
		break;
	case IAVF_LINK_SPEED_100MB:
		speed = "100 M";
		break;
	default:
		break;
	}

	netdev_info(netdev, "NIC Link is Up %sbps Full Duplex\n", speed);
}