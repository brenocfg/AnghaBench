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
struct mlx5_vxlan_port {int /*<<< orphan*/  hlist; int /*<<< orphan*/  refcount; int /*<<< orphan*/  udp_port; } ;
struct mlx5_vxlan {scalar_t__ num_ports; int /*<<< orphan*/  sync_lock; int /*<<< orphan*/  mdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  htable; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_vxlan_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int mlx5_vxlan_core_add_port_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_vxlan_core_del_port_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_vxlan_port* mlx5_vxlan_lookup_port (struct mlx5_vxlan*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_vxlan_max_udp_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mlx5_vxlan_add_port(struct mlx5_vxlan *vxlan, u16 port)
{
	struct mlx5_vxlan_port *vxlanp;
	int ret = -ENOSPC;

	vxlanp = mlx5_vxlan_lookup_port(vxlan, port);
	if (vxlanp) {
		refcount_inc(&vxlanp->refcount);
		return 0;
	}

	mutex_lock(&vxlan->sync_lock);
	if (vxlan->num_ports >= mlx5_vxlan_max_udp_ports(vxlan->mdev)) {
		mlx5_core_info(vxlan->mdev,
			       "UDP port (%d) not offloaded, max number of UDP ports (%d) are already offloaded\n",
			       port, mlx5_vxlan_max_udp_ports(vxlan->mdev));
		ret = -ENOSPC;
		goto unlock;
	}

	ret = mlx5_vxlan_core_add_port_cmd(vxlan->mdev, port);
	if (ret)
		goto unlock;

	vxlanp = kzalloc(sizeof(*vxlanp), GFP_KERNEL);
	if (!vxlanp) {
		ret = -ENOMEM;
		goto err_delete_port;
	}

	vxlanp->udp_port = port;
	refcount_set(&vxlanp->refcount, 1);

	spin_lock_bh(&vxlan->lock);
	hash_add(vxlan->htable, &vxlanp->hlist, port);
	spin_unlock_bh(&vxlan->lock);

	vxlan->num_ports++;
	mutex_unlock(&vxlan->sync_lock);
	return 0;

err_delete_port:
	mlx5_vxlan_core_del_port_cmd(vxlan->mdev, port);

unlock:
	mutex_unlock(&vxlan->sync_lock);
	return ret;
}