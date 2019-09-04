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
typedef  int /*<<< orphan*/  u8 ;
struct usnic_ib_dev {struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct usnic_ib_dev* to_usdev (struct ib_device*) ; 

struct net_device *usnic_get_netdev(struct ib_device *device, u8 port_num)
{
	struct usnic_ib_dev *us_ibdev = to_usdev(device);

	if (us_ibdev->netdev)
		dev_hold(us_ibdev->netdev);

	return us_ibdev->netdev;
}