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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int flags; } ;
struct mlxsw_sp_span_parms {int /*<<< orphan*/  vid; int /*<<< orphan*/  dest_port; } ;

/* Variables and functions */
 int IFF_UP ; 
 int mlxsw_sp_span_entry_unoffloadable (struct mlxsw_sp_span_parms*) ; 
 struct net_device* mlxsw_sp_span_entry_vlan (struct net_device const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mlxsw_sp_span_entry_vlan_parms(const struct net_device *to_dev,
			       struct mlxsw_sp_span_parms *sparmsp)
{
	struct net_device *real_dev;
	u16 vid;

	if (!(to_dev->flags & IFF_UP))
		return mlxsw_sp_span_entry_unoffloadable(sparmsp);

	real_dev = mlxsw_sp_span_entry_vlan(to_dev, &vid);
	sparmsp->dest_port = netdev_priv(real_dev);
	sparmsp->vid = vid;
	return 0;
}