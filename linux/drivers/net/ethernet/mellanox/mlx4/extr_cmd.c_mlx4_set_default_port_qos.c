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
struct mlx4_qos_manager {int /*<<< orphan*/  priority_bm; } ;
struct TYPE_3__ {struct mlx4_qos_manager* qos_ctl; } ;
struct TYPE_4__ {TYPE_1__ master; } ;
struct mlx4_priv {TYPE_2__ mfunc; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DEFAULT_QOS_PRIO ; 
 int /*<<< orphan*/  MLX4_NUM_UP ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_set_default_port_qos(struct mlx4_dev *dev, int port)
{
	struct mlx4_qos_manager *port_qos_ctl;
	struct mlx4_priv *priv = mlx4_priv(dev);

	port_qos_ctl = &priv->mfunc.master.qos_ctl[port];
	bitmap_zero(port_qos_ctl->priority_bm, MLX4_NUM_UP);

	/* Enable only default prio at PF init routine */
	set_bit(MLX4_DEFAULT_QOS_PRIO, port_qos_ctl->priority_bm);
}