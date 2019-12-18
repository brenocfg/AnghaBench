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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PEFA_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_pack (char*,int /*<<< orphan*/ ,int,char*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pefa ; 

__attribute__((used)) static int mlxsw_sp_act_kvdl_set_add(void *priv, u32 *p_kvdl_index,
				     char *enc_actions, bool is_first, bool ca)
{
	struct mlxsw_sp *mlxsw_sp = priv;
	char pefa_pl[MLXSW_REG_PEFA_LEN];
	u32 kvdl_index;
	int err;

	/* The first action set of a TCAM entry is stored directly in TCAM,
	 * not KVD linear area.
	 */
	if (is_first)
		return 0;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
				  1, &kvdl_index);
	if (err)
		return err;
	mlxsw_reg_pefa_pack(pefa_pl, kvdl_index, ca, enc_actions);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pefa), pefa_pl);
	if (err)
		goto err_pefa_write;
	*p_kvdl_index = kvdl_index;
	return 0;

err_pefa_write:
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   1, kvdl_index);
	return err;
}