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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  netdev_warn_once (struct net_device*,char*) ; 

__attribute__((used)) static int mlx5e_uplink_rep_set_vf_vlan(struct net_device *dev, int vf, u16 vlan, u8 qos,
					__be16 vlan_proto)
{
	netdev_warn_once(dev, "legacy vf vlan setting isn't supported in switchdev mode\n");

	if (vlan != 0)
		return -EOPNOTSUPP;

	/* allow setting 0-vid for compatibility with libvirt */
	return 0;
}