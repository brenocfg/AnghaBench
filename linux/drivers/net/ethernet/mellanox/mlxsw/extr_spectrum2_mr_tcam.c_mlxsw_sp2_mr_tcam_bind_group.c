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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_pemrbt_protocol { ____Placeholder_mlxsw_reg_pemrbt_protocol } mlxsw_reg_pemrbt_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PEMRBT_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pemrbt_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_group_id (struct mlxsw_sp_acl_ruleset*) ; 
 int /*<<< orphan*/  pemrbt ; 

__attribute__((used)) static int mlxsw_sp2_mr_tcam_bind_group(struct mlxsw_sp *mlxsw_sp,
					enum mlxsw_reg_pemrbt_protocol protocol,
					struct mlxsw_sp_acl_ruleset *ruleset)
{
	char pemrbt_pl[MLXSW_REG_PEMRBT_LEN];
	u16 group_id;

	group_id = mlxsw_sp_acl_ruleset_group_id(ruleset);

	mlxsw_reg_pemrbt_pack(pemrbt_pl, protocol, group_id);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pemrbt), pemrbt_pl);
}