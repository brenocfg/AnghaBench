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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_bridge_vxlan_dev_find (struct net_device*) ; 

__attribute__((used)) static inline bool mlxsw_sp_bridge_has_vxlan(struct net_device *br_dev)
{
	return !!mlxsw_sp_bridge_vxlan_dev_find(br_dev);
}