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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int dummy; } ;

/* Variables and functions */
 int __ice_set_coalesce (struct net_device*,struct ethtool_coalesce*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ice_set_per_q_coalesce(struct net_device *netdev, u32 q_num,
		       struct ethtool_coalesce *ec)
{
	return __ice_set_coalesce(netdev, ec, q_num);
}