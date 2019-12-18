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
struct mlxsw_sp2_acl_tcam {int /*<<< orphan*/  kvdl_index; int /*<<< orphan*/  kvdl_count; int /*<<< orphan*/  atcam; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_fini (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp2_acl_tcam_fini(struct mlxsw_sp *mlxsw_sp, void *priv)
{
	struct mlxsw_sp2_acl_tcam *tcam = priv;

	mlxsw_sp_acl_atcam_fini(mlxsw_sp, &tcam->atcam);
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   tcam->kvdl_count, tcam->kvdl_index);
}