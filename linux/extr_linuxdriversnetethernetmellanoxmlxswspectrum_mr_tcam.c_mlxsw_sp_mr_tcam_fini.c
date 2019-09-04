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
struct mlxsw_sp_mr_tcam_ops {int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_mr_tcam {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp {struct mlxsw_sp_mr_tcam_ops* mr_tcam_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_mr_tcam_fini(struct mlxsw_sp *mlxsw_sp, void *priv)
{
	const struct mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	struct mlxsw_sp_mr_tcam *mr_tcam = priv;

	ops->fini(mr_tcam->priv);
	kfree(mr_tcam->priv);
}