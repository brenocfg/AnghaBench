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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {struct net_device** netdevs; } ;
struct hns_roce_dev {TYPE_1__ iboe; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
#define  NETDEV_CHANGE 132 
#define  NETDEV_CHANGEADDR 131 
#define  NETDEV_DOWN 130 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 int hns_roce_set_mac (struct hns_roce_dev*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_en_event(struct hns_roce_dev *hr_dev, u8 port,
			   unsigned long event)
{
	struct device *dev = hr_dev->dev;
	struct net_device *netdev;
	int ret = 0;

	netdev = hr_dev->iboe.netdevs[port];
	if (!netdev) {
		dev_err(dev, "port(%d) can't find netdev\n", port);
		return -ENODEV;
	}

	switch (event) {
	case NETDEV_UP:
	case NETDEV_CHANGE:
	case NETDEV_REGISTER:
	case NETDEV_CHANGEADDR:
		ret = hns_roce_set_mac(hr_dev, port, netdev->dev_addr);
		break;
	case NETDEV_DOWN:
		/*
		 * In v1 engine, only support all ports closed together.
		 */
		break;
	default:
		dev_dbg(dev, "NETDEV event = 0x%x!\n", (u32)(event));
		break;
	}

	return ret;
}