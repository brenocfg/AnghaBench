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
struct net_device {scalar_t__ dev_addr; } ;
struct i40iw_device {struct net_device* netdev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_add_ipv4_addr (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_add_ipv6_addr (struct i40iw_device*) ; 
 int i40iw_alloc_set_mac_ipaddr (struct i40iw_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_add_mac_ip(struct i40iw_device *iwdev)
{
	struct net_device *netdev = iwdev->netdev;
	enum i40iw_status_code status;

	status = i40iw_alloc_set_mac_ipaddr(iwdev, (u8 *)netdev->dev_addr);
	if (status)
		return status;
	i40iw_add_ipv4_addr(iwdev);
	i40iw_add_ipv6_addr(iwdev);
	return 0;
}