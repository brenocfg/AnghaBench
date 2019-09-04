#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx4_set_port_general_context {scalar_t__ pptx; scalar_t__ pprx; } ;
struct mlx4_mfunc_master_ctx {scalar_t__ pptx; scalar_t__ pprx; } ;
struct TYPE_2__ {struct mlx4_mfunc_master_ctx master; } ;
struct mlx4_priv {TYPE_1__ mfunc; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 

__attribute__((used)) static void
mlx4_en_set_port_global_pause(struct mlx4_dev *dev, int slave,
			      struct mlx4_set_port_general_context *gen_context)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_mfunc_master_ctx *master = &priv->mfunc.master;

	/* Slave cannot change Global Pause configuration */
	if (slave != mlx4_master_func_num(dev) &&
	    (gen_context->pptx != master->pptx ||
	     gen_context->pprx != master->pprx)) {
		gen_context->pptx = master->pptx;
		gen_context->pprx = master->pprx;
		mlx4_warn(dev, "denying Global Pause change for slave:%d\n",
			  slave);
	} else {
		master->pptx = gen_context->pptx;
		master->pprx = gen_context->pprx;
	}
}