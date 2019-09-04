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
struct mlx5_vxlan_port {int dummy; } ;
struct mlx5_vxlan {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_vxlan_allowed (struct mlx5_vxlan*) ; 
 struct mlx5_vxlan_port* mlx5_vxlan_lookup_port_locked (struct mlx5_vxlan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct mlx5_vxlan_port *mlx5_vxlan_lookup_port(struct mlx5_vxlan *vxlan, u16 port)
{
	struct mlx5_vxlan_port *vxlanp;

	if (!mlx5_vxlan_allowed(vxlan))
		return NULL;

	spin_lock_bh(&vxlan->lock);
	vxlanp = mlx5_vxlan_lookup_port_locked(vxlan, port);
	spin_unlock_bh(&vxlan->lock);

	return vxlanp;
}