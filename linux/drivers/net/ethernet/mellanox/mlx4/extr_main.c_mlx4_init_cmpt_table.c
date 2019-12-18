#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_12__ {int /*<<< orphan*/  cmpt_table; } ;
struct TYPE_11__ {int /*<<< orphan*/  cmpt_table; } ;
struct TYPE_10__ {int /*<<< orphan*/  cmpt_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmpt_table; } ;
struct mlx4_priv {TYPE_6__ qp_table; TYPE_5__ srq_table; TYPE_4__ cq_table; TYPE_3__ eq_table; } ;
struct TYPE_8__ {int num_phys_eqs; } ;
struct TYPE_7__ {int num_qps; int* reserved_qps_cnt; int num_srqs; int reserved_srqs; int num_cqs; int reserved_cqs; } ;
struct mlx4_dev {TYPE_2__ phys_caps; TYPE_1__ caps; } ;

/* Variables and functions */
 int MLX4_CMPT_SHIFT ; 
 int MLX4_CMPT_TYPE_CQ ; 
 int MLX4_CMPT_TYPE_EQ ; 
 int MLX4_CMPT_TYPE_QP ; 
 int MLX4_CMPT_TYPE_SRQ ; 
 size_t MLX4_QP_REGION_FW ; 
 int /*<<< orphan*/  mlx4_cleanup_icm_table (struct mlx4_dev*,int /*<<< orphan*/ *) ; 
 int mlx4_init_icm_table (struct mlx4_dev*,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_init_cmpt_table(struct mlx4_dev *dev, u64 cmpt_base,
				int cmpt_entry_sz)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int err;
	int num_eqs;

	err = mlx4_init_icm_table(dev, &priv->qp_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_QP *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, dev->caps.num_qps,
				  dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
				  0, 0);
	if (err)
		goto err;

	err = mlx4_init_icm_table(dev, &priv->srq_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_SRQ *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, dev->caps.num_srqs,
				  dev->caps.reserved_srqs, 0, 0);
	if (err)
		goto err_qp;

	err = mlx4_init_icm_table(dev, &priv->cq_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_CQ *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, dev->caps.num_cqs,
				  dev->caps.reserved_cqs, 0, 0);
	if (err)
		goto err_srq;

	num_eqs = dev->phys_caps.num_phys_eqs;
	err = mlx4_init_icm_table(dev, &priv->eq_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_EQ *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, num_eqs, num_eqs, 0, 0);
	if (err)
		goto err_cq;

	return 0;

err_cq:
	mlx4_cleanup_icm_table(dev, &priv->cq_table.cmpt_table);

err_srq:
	mlx4_cleanup_icm_table(dev, &priv->srq_table.cmpt_table);

err_qp:
	mlx4_cleanup_icm_table(dev, &priv->qp_table.cmpt_table);

err:
	return err;
}