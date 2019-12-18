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
struct net_device {TYPE_1__* phydev; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ link; int speed; int duplex; } ;

/* Variables and functions */
 int hclge_cfg_flowctrl (struct hclge_dev*) ; 
 int hclge_cfg_mac_speed_dup (struct hclge_dev*,int,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hclge_mac_adjust_link(struct net_device *netdev)
{
	struct hnae3_handle *h = *((void **)netdev_priv(netdev));
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;
	int duplex, speed;
	int ret;

	/* When phy link down, do nothing */
	if (netdev->phydev->link == 0)
		return;

	speed = netdev->phydev->speed;
	duplex = netdev->phydev->duplex;

	ret = hclge_cfg_mac_speed_dup(hdev, speed, duplex);
	if (ret)
		netdev_err(netdev, "failed to adjust link.\n");

	ret = hclge_cfg_flowctrl(hdev);
	if (ret)
		netdev_err(netdev, "failed to configure flow control.\n");
}