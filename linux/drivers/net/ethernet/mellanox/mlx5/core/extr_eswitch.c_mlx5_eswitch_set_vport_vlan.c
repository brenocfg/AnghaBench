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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int SET_VLAN_INSERT ; 
 int SET_VLAN_STRIP ; 
 int __mlx5_eswitch_set_vport_vlan (struct mlx5_eswitch*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_set_vport_vlan(struct mlx5_eswitch *esw,
				u16 vport, u16 vlan, u8 qos)
{
	u8 set_flags = 0;
	int err;

	if (vlan || qos)
		set_flags = SET_VLAN_STRIP | SET_VLAN_INSERT;

	mutex_lock(&esw->state_lock);
	err = __mlx5_eswitch_set_vport_vlan(esw, vport, vlan, qos, set_flags);
	mutex_unlock(&esw->state_lock);

	return err;
}