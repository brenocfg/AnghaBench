#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_hca_vport_context {scalar_t__ policy; int field_select; scalar_t__ node_guid; scalar_t__ port_guid; } ;
struct mlx5_core_sriov {TYPE_2__* vfs_ctx; } ;
struct TYPE_3__ {struct mlx5_core_sriov sriov; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_4__ {scalar_t__ policy; scalar_t__ port_guid; scalar_t__ node_guid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_HCA_VPORT_SEL_NODE_GUID ; 
 int MLX5_HCA_VPORT_SEL_PORT_GUID ; 
 int MLX5_HCA_VPORT_SEL_STATE_POLICY ; 
 scalar_t__ MLX5_POLICY_INVALID ; 
 int /*<<< orphan*/  kfree (struct mlx5_hca_vport_context*) ; 
 struct mlx5_hca_vport_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_modify_hca_vport_context (struct mlx5_core_dev*,int,int,int,struct mlx5_hca_vport_context*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 

__attribute__((used)) static int sriov_restore_guids(struct mlx5_core_dev *dev, int vf)
{
	struct mlx5_core_sriov *sriov = &dev->priv.sriov;
	struct mlx5_hca_vport_context *in;
	int err = 0;

	/* Restore sriov guid and policy settings */
	if (sriov->vfs_ctx[vf].node_guid ||
	    sriov->vfs_ctx[vf].port_guid ||
	    sriov->vfs_ctx[vf].policy != MLX5_POLICY_INVALID) {
		in = kzalloc(sizeof(*in), GFP_KERNEL);
		if (!in)
			return -ENOMEM;

		in->node_guid = sriov->vfs_ctx[vf].node_guid;
		in->port_guid = sriov->vfs_ctx[vf].port_guid;
		in->policy = sriov->vfs_ctx[vf].policy;
		in->field_select =
			!!(in->port_guid) * MLX5_HCA_VPORT_SEL_PORT_GUID |
			!!(in->node_guid) * MLX5_HCA_VPORT_SEL_NODE_GUID |
			!!(in->policy) * MLX5_HCA_VPORT_SEL_STATE_POLICY;

		err = mlx5_core_modify_hca_vport_context(dev, 1, 1, vf + 1, in);
		if (err)
			mlx5_core_warn(dev, "modify vport context failed, unable to restore VF %d settings\n", vf);

		kfree(in);
	}

	return err;
}