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
struct mlxsw_sp_acl_erp_core {int /*<<< orphan*/  erp_tables; int /*<<< orphan*/  bf; void* num_erp_banks; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_ERPT_BANKS ; 
 int /*<<< orphan*/  ACL_MAX_ERPT_BANK_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_ERP_GENALLOC_OFFSET ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int gen_pool_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  gen_pool_best_fit ; 
 int /*<<< orphan*/  gen_pool_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_set_algo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_bf_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_bf_init (struct mlxsw_sp*,void*) ; 
 int mlxsw_sp_acl_erp_tables_sizes_query (struct mlxsw_sp*,struct mlxsw_sp_acl_erp_core*) ; 

__attribute__((used)) static int mlxsw_sp_acl_erp_tables_init(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_acl_erp_core *erp_core)
{
	unsigned int erpt_bank_size;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_ERPT_BANK_SIZE) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_ERPT_BANKS))
		return -EIO;
	erpt_bank_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					    ACL_MAX_ERPT_BANK_SIZE);
	erp_core->num_erp_banks = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						     ACL_MAX_ERPT_BANKS);

	erp_core->erp_tables = gen_pool_create(0, -1);
	if (!erp_core->erp_tables)
		return -ENOMEM;
	gen_pool_set_algo(erp_core->erp_tables, gen_pool_best_fit, NULL);

	err = gen_pool_add(erp_core->erp_tables,
			   MLXSW_SP_ACL_ERP_GENALLOC_OFFSET, erpt_bank_size,
			   -1);
	if (err)
		goto err_gen_pool_add;

	erp_core->bf = mlxsw_sp_acl_bf_init(mlxsw_sp, erp_core->num_erp_banks);
	if (IS_ERR(erp_core->bf)) {
		err = PTR_ERR(erp_core->bf);
		goto err_bf_init;
	}

	/* Different regions require masks of different sizes */
	err = mlxsw_sp_acl_erp_tables_sizes_query(mlxsw_sp, erp_core);
	if (err)
		goto err_erp_tables_sizes_query;

	return 0;

err_erp_tables_sizes_query:
	mlxsw_sp_acl_bf_fini(erp_core->bf);
err_bf_init:
err_gen_pool_add:
	gen_pool_destroy(erp_core->erp_tables);
	return err;
}