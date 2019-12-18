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
struct ethtool_coalesce {int dummy; } ;

/* Variables and functions */
 int __i40e_get_coalesce (struct net_device*,struct ethtool_coalesce*,int) ; 

__attribute__((used)) static int i40e_get_coalesce(struct net_device *netdev,
			     struct ethtool_coalesce *ec)
{
	return __i40e_get_coalesce(netdev, ec, -1);
}