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
struct mlxsw_sp_fid_family {int dummy; } ;
struct mlxsw_sp_fid_core {int /*<<< orphan*/  fid_ht; int /*<<< orphan*/  vni_ht; struct mlxsw_sp_fid_core* port_fid_mappings; struct mlxsw_sp_fid_family** fid_family_arr; } ;
struct mlxsw_sp {struct mlxsw_sp_fid_core* fid_core; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLXSW_SP_FID_TYPE_MAX ; 
 struct mlxsw_sp_fid_core* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fid_core*) ; 
 struct mlxsw_sp_fid_core* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlxsw_sp_fid_family_arr ; 
 int mlxsw_sp_fid_family_register (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_family_unregister (struct mlxsw_sp*,struct mlxsw_sp_fid_family*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_fid_vni_ht_params ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_sp_fids_init(struct mlxsw_sp *mlxsw_sp)
{
	unsigned int max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	struct mlxsw_sp_fid_core *fid_core;
	int err, i;

	fid_core = kzalloc(sizeof(*mlxsw_sp->fid_core), GFP_KERNEL);
	if (!fid_core)
		return -ENOMEM;
	mlxsw_sp->fid_core = fid_core;

	err = rhashtable_init(&fid_core->fid_ht, &mlxsw_sp_fid_ht_params);
	if (err)
		goto err_rhashtable_fid_init;

	err = rhashtable_init(&fid_core->vni_ht, &mlxsw_sp_fid_vni_ht_params);
	if (err)
		goto err_rhashtable_vni_init;

	fid_core->port_fid_mappings = kcalloc(max_ports, sizeof(unsigned int),
					      GFP_KERNEL);
	if (!fid_core->port_fid_mappings) {
		err = -ENOMEM;
		goto err_alloc_port_fid_mappings;
	}

	for (i = 0; i < MLXSW_SP_FID_TYPE_MAX; i++) {
		err = mlxsw_sp_fid_family_register(mlxsw_sp,
						   mlxsw_sp_fid_family_arr[i]);

		if (err)
			goto err_fid_ops_register;
	}

	return 0;

err_fid_ops_register:
	for (i--; i >= 0; i--) {
		struct mlxsw_sp_fid_family *fid_family;

		fid_family = fid_core->fid_family_arr[i];
		mlxsw_sp_fid_family_unregister(mlxsw_sp, fid_family);
	}
	kfree(fid_core->port_fid_mappings);
err_alloc_port_fid_mappings:
	rhashtable_destroy(&fid_core->vni_ht);
err_rhashtable_vni_init:
	rhashtable_destroy(&fid_core->fid_ht);
err_rhashtable_fid_init:
	kfree(fid_core);
	return err;
}