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
struct mlx5_vxlan_port {int /*<<< orphan*/  hlist; int /*<<< orphan*/  refcount; } ;
struct mlx5_vxlan {int /*<<< orphan*/  sync_lock; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  mdev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_vxlan_port*) ; 
 int /*<<< orphan*/  mlx5_vxlan_core_del_port_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_vxlan_port* mlx5_vxlan_lookup_port_locked (struct mlx5_vxlan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mlx5_vxlan_del_port(struct mlx5_vxlan *vxlan, u16 port)
{
	struct mlx5_vxlan_port *vxlanp;
	bool remove = false;
	int ret = 0;

	mutex_lock(&vxlan->sync_lock);

	spin_lock_bh(&vxlan->lock);
	vxlanp = mlx5_vxlan_lookup_port_locked(vxlan, port);
	if (!vxlanp) {
		ret = -ENOENT;
		goto out_unlock;
	}

	if (refcount_dec_and_test(&vxlanp->refcount)) {
		hash_del(&vxlanp->hlist);
		remove = true;
	}

out_unlock:
	spin_unlock_bh(&vxlan->lock);

	if (remove) {
		mlx5_vxlan_core_del_port_cmd(vxlan->mdev, port);
		kfree(vxlanp);
		vxlan->num_ports--;
	}

	mutex_unlock(&vxlan->sync_lock);

	return ret;
}