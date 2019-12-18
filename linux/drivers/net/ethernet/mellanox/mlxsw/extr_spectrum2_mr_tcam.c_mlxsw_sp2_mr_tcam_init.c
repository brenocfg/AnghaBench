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
struct mlxsw_sp2_mr_tcam {int /*<<< orphan*/  acl_block; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mlxsw_sp2_mr_tcam_ipv4_fini (struct mlxsw_sp2_mr_tcam*) ; 
 int mlxsw_sp2_mr_tcam_ipv4_init (struct mlxsw_sp2_mr_tcam*) ; 
 int mlxsw_sp2_mr_tcam_ipv6_init (struct mlxsw_sp2_mr_tcam*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_create (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp2_mr_tcam_init(struct mlxsw_sp *mlxsw_sp, void *priv)
{
	struct mlxsw_sp2_mr_tcam *mr_tcam = priv;
	int err;

	mr_tcam->mlxsw_sp = mlxsw_sp;
	mr_tcam->acl_block = mlxsw_sp_acl_block_create(mlxsw_sp, NULL);
	if (!mr_tcam->acl_block)
		return -ENOMEM;

	err = mlxsw_sp2_mr_tcam_ipv4_init(mr_tcam);
	if (err)
		goto err_ipv4_init;

	err = mlxsw_sp2_mr_tcam_ipv6_init(mr_tcam);
	if (err)
		goto err_ipv6_init;

	return 0;

err_ipv6_init:
	mlxsw_sp2_mr_tcam_ipv4_fini(mr_tcam);
err_ipv4_init:
	mlxsw_sp_acl_block_destroy(mr_tcam->acl_block);
	return err;
}