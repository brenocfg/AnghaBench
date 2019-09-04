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
 scalar_t__ is_vlan_dev (struct net_device const*) ; 
 scalar_t__ mlxsw_sp_port_dev_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_dev_real_dev (struct net_device const*) ; 

__attribute__((used)) static bool
mlxsw_sp_span_vlan_can_handle(const struct net_device *dev)
{
	return is_vlan_dev(dev) &&
	       mlxsw_sp_port_dev_check(vlan_dev_real_dev(dev));
}