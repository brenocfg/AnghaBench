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
struct mlxsw_sp2_mr_tcam {int /*<<< orphan*/  acl_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp2_mr_tcam_ipv4_fini (struct mlxsw_sp2_mr_tcam*) ; 
 int /*<<< orphan*/  mlxsw_sp2_mr_tcam_ipv6_fini (struct mlxsw_sp2_mr_tcam*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp2_mr_tcam_fini(void *priv)
{
	struct mlxsw_sp2_mr_tcam *mr_tcam = priv;

	mlxsw_sp2_mr_tcam_ipv6_fini(mr_tcam);
	mlxsw_sp2_mr_tcam_ipv4_fini(mr_tcam);
	mlxsw_sp_acl_block_destroy(mr_tcam->acl_block);
}