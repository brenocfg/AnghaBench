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
struct mlx5_vxlan {int /*<<< orphan*/  htable; int /*<<< orphan*/  lock; int /*<<< orphan*/  sync_lock; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 struct mlx5_vxlan* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IANA_VXLAN_UDP_PORT ; 
 int /*<<< orphan*/  MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 struct mlx5_vxlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_vxlan_add_port (struct mlx5_vxlan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tunnel_stateless_vxlan ; 

struct mlx5_vxlan *mlx5_vxlan_create(struct mlx5_core_dev *mdev)
{
	struct mlx5_vxlan *vxlan;

	if (!MLX5_CAP_ETH(mdev, tunnel_stateless_vxlan) || !mlx5_core_is_pf(mdev))
		return ERR_PTR(-ENOTSUPP);

	vxlan = kzalloc(sizeof(*vxlan), GFP_KERNEL);
	if (!vxlan)
		return ERR_PTR(-ENOMEM);

	vxlan->mdev = mdev;
	mutex_init(&vxlan->sync_lock);
	spin_lock_init(&vxlan->lock);
	hash_init(vxlan->htable);

	/* Hardware adds 4789 (IANA_VXLAN_UDP_PORT) by default */
	mlx5_vxlan_add_port(vxlan, IANA_VXLAN_UDP_PORT);

	return vxlan;
}