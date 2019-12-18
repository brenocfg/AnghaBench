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
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_hca_vport_context {int /*<<< orphan*/  policy; } ;
struct mlx5_core_dev {int dummy; } ;
struct ifla_vf_info {int /*<<< orphan*/  linkstate; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __IFLA_VF_LINK_STATE_MAX ; 
 int /*<<< orphan*/  kfree (struct mlx5_hca_vport_context*) ; 
 struct mlx5_hca_vport_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifla_vf_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int) ; 
 int mlx5_query_hca_vport_context (struct mlx5_core_dev*,int,int,int,struct mlx5_hca_vport_context*) ; 
 int /*<<< orphan*/  mlx_to_net_policy (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

int mlx5_ib_get_vf_config(struct ib_device *device, int vf, u8 port,
			  struct ifla_vf_info *info)
{
	struct mlx5_ib_dev *dev = to_mdev(device);
	struct mlx5_core_dev *mdev = dev->mdev;
	struct mlx5_hca_vport_context *rep;
	int err;

	rep = kzalloc(sizeof(*rep), GFP_KERNEL);
	if (!rep)
		return -ENOMEM;

	err = mlx5_query_hca_vport_context(mdev, 1, 1,  vf + 1, rep);
	if (err) {
		mlx5_ib_warn(dev, "failed to query port policy for vf %d (%d)\n",
			     vf, err);
		goto free;
	}
	memset(info, 0, sizeof(*info));
	info->linkstate = mlx_to_net_policy(rep->policy);
	if (info->linkstate == __IFLA_VF_LINK_STATE_MAX)
		err = -EINVAL;

free:
	kfree(rep);
	return err;
}