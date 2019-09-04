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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PPBS_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_PBS ; 
 int /*<<< orphan*/  mlxsw_reg_ppbs_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppbs ; 

__attribute__((used)) static int mlxsw_sp_act_kvdl_fwd_entry_add(void *priv, u32 *p_kvdl_index,
					   u8 local_port)
{
	struct mlxsw_sp *mlxsw_sp = priv;
	char ppbs_pl[MLXSW_REG_PPBS_LEN];
	u32 kvdl_index;
	int err;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_PBS,
				  1, &kvdl_index);
	if (err)
		return err;
	mlxsw_reg_ppbs_pack(ppbs_pl, kvdl_index, local_port);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ppbs), ppbs_pl);
	if (err)
		goto err_ppbs_write;
	*p_kvdl_index = kvdl_index;
	return 0;

err_ppbs_write:
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_PBS,
			   1, kvdl_index);
	return err;
}