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
struct TYPE_10__ {TYPE_3__* res_alloc; } ;
struct TYPE_11__ {TYPE_4__ res_tracker; } ;
struct TYPE_12__ {TYPE_5__ master; } ;
struct mlx4_priv {TYPE_6__ mfunc; } ;
struct TYPE_8__ {scalar_t__ mpt; scalar_t__ mtt; scalar_t__ srq; scalar_t__ cq; scalar_t__ qp; } ;
struct TYPE_7__ {scalar_t__ reserved_mrws; scalar_t__ num_mpts; scalar_t__ reserved_mtts; scalar_t__ num_mtts; scalar_t__ reserved_srqs; scalar_t__ num_srqs; scalar_t__ reserved_cqs; scalar_t__ num_cqs; scalar_t__ reserved_qps; scalar_t__ num_qps; } ;
struct mlx4_dev {TYPE_2__ quotas; TYPE_1__ caps; } ;
struct TYPE_9__ {scalar_t__* quota; } ;

/* Variables and functions */
 size_t RES_CQ ; 
 size_t RES_MPT ; 
 size_t RES_MTT ; 
 size_t RES_QP ; 
 size_t RES_SRQ ; 
 int /*<<< orphan*/  mlx4_is_mfunc (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 scalar_t__ mlx4_num_reserved_sqps (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_init_quotas(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int pf;

	/* quotas for VFs are initialized in mlx4_slave_cap */
	if (mlx4_is_slave(dev))
		return;

	if (!mlx4_is_mfunc(dev)) {
		dev->quotas.qp = dev->caps.num_qps - dev->caps.reserved_qps -
			mlx4_num_reserved_sqps(dev);
		dev->quotas.cq = dev->caps.num_cqs - dev->caps.reserved_cqs;
		dev->quotas.srq = dev->caps.num_srqs - dev->caps.reserved_srqs;
		dev->quotas.mtt = dev->caps.num_mtts - dev->caps.reserved_mtts;
		dev->quotas.mpt = dev->caps.num_mpts - dev->caps.reserved_mrws;
		return;
	}

	pf = mlx4_master_func_num(dev);
	dev->quotas.qp =
		priv->mfunc.master.res_tracker.res_alloc[RES_QP].quota[pf];
	dev->quotas.cq =
		priv->mfunc.master.res_tracker.res_alloc[RES_CQ].quota[pf];
	dev->quotas.srq =
		priv->mfunc.master.res_tracker.res_alloc[RES_SRQ].quota[pf];
	dev->quotas.mtt =
		priv->mfunc.master.res_tracker.res_alloc[RES_MTT].quota[pf];
	dev->quotas.mpt =
		priv->mfunc.master.res_tracker.res_alloc[RES_MPT].quota[pf];
}