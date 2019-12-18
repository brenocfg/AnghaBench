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
struct mlxsw_sp_acl_tcam {int max_regions; } ;
struct mlxsw_sp2_acl_tcam {int kvdl_count; scalar_t__ kvdl_index; int /*<<< orphan*/  atcam; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; int /*<<< orphan*/  afa; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PEFA_LEN ; 
 int MLXSW_REG_PGCR_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET ; 
 scalar_t__ WARN_ON (int) ; 
 int mlxsw_afa_block_continue (struct mlxsw_afa_block*) ; 
 struct mlxsw_afa_block* mlxsw_afa_block_create (int /*<<< orphan*/ ) ; 
 char* mlxsw_afa_block_cur_set (struct mlxsw_afa_block*) ; 
 int /*<<< orphan*/  mlxsw_afa_block_destroy (struct mlxsw_afa_block*) ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_pack (char*,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_pgcr_pack (char*,scalar_t__) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_acl_atcam_init (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  pefa ; 
 int /*<<< orphan*/  pgcr ; 

__attribute__((used)) static int mlxsw_sp2_acl_tcam_init(struct mlxsw_sp *mlxsw_sp, void *priv,
				   struct mlxsw_sp_acl_tcam *_tcam)
{
	struct mlxsw_sp2_acl_tcam *tcam = priv;
	struct mlxsw_afa_block *afa_block;
	char pefa_pl[MLXSW_REG_PEFA_LEN];
	char pgcr_pl[MLXSW_REG_PGCR_LEN];
	char *enc_actions;
	int i;
	int err;

	tcam->kvdl_count = _tcam->max_regions;
	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
				  tcam->kvdl_count, &tcam->kvdl_index);
	if (err)
		return err;

	/* Create flex action block, set default action (continue)
	 * but don't commit. We need just the current set encoding
	 * to be written using PEFA register to all indexes for all regions.
	 */
	afa_block = mlxsw_afa_block_create(mlxsw_sp->afa);
	if (!afa_block) {
		err = -ENOMEM;
		goto err_afa_block;
	}
	err = mlxsw_afa_block_continue(afa_block);
	if (WARN_ON(err))
		goto err_afa_block_continue;
	enc_actions = mlxsw_afa_block_cur_set(afa_block);

	for (i = 0; i < tcam->kvdl_count; i++) {
		mlxsw_reg_pefa_pack(pefa_pl, tcam->kvdl_index + i,
				    true, enc_actions);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pefa), pefa_pl);
		if (err)
			goto err_pefa_write;
	}
	mlxsw_reg_pgcr_pack(pgcr_pl, tcam->kvdl_index);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pgcr), pgcr_pl);
	if (err)
		goto err_pgcr_write;

	err = mlxsw_sp_acl_atcam_init(mlxsw_sp, &tcam->atcam);
	if (err)
		goto err_atcam_init;

	mlxsw_afa_block_destroy(afa_block);
	return 0;

err_atcam_init:
err_pgcr_write:
err_pefa_write:
err_afa_block_continue:
	mlxsw_afa_block_destroy(afa_block);
err_afa_block:
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   tcam->kvdl_count, tcam->kvdl_index);
	return err;
}