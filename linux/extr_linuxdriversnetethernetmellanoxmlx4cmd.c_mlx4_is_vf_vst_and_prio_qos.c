#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vport_state {scalar_t__ default_vlan; int /*<<< orphan*/  default_qos; } ;
struct mlx4_qos_manager {int /*<<< orphan*/  priority_bm; } ;
struct TYPE_5__ {struct mlx4_qos_manager* qos_ctl; } ;
struct TYPE_6__ {TYPE_2__ master; } ;
struct mlx4_priv {TYPE_3__ mfunc; } ;
struct TYPE_4__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_FLAG2_QOS_VPP ; 
 scalar_t__ MLX4_VGT ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlx4_is_vf_vst_and_prio_qos(struct mlx4_dev *dev, int port,
					struct mlx4_vport_state *vf_admin)
{
	struct mlx4_qos_manager *info;
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (!mlx4_is_master(dev) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QOS_VPP))
		return false;

	info = &priv->mfunc.master.qos_ctl[port];

	if (vf_admin->default_vlan != MLX4_VGT &&
	    test_bit(vf_admin->default_qos, info->priority_bm))
		return true;

	return false;
}