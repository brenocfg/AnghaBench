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
struct TYPE_5__ {TYPE_1__* vf_oper; } ;
struct TYPE_6__ {TYPE_2__ master; } ;
struct mlx4_priv {TYPE_3__ mfunc; } ;
struct mlx4_dev {int num_slaves; } ;
struct TYPE_4__ {scalar_t__* smi_enabled; } ;

/* Variables and functions */
 int MLX4_MAX_PORTS ; 
 scalar_t__ MLX4_VF_SMI_ENABLED ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_vf_smi_enabled(struct mlx4_dev *dev, int slave, int port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (slave < 1 || slave >= dev->num_slaves ||
	    port < 1 || port > MLX4_MAX_PORTS)
		return 0;

	return priv->mfunc.master.vf_oper[slave].smi_enabled[port] ==
		MLX4_VF_SMI_ENABLED;
}