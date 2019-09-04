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
typedef  size_t u8 ;
struct mlxsw_sp {int /*<<< orphan*/ * ports; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 unsigned int MASKED_COUNT_MAX ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_SBSR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_EGRESS ; 
 int /*<<< orphan*/  MLXSW_REG_SBXX_DIR_INGRESS ; 
 int MLXSW_SP_SB_POOL_COUNT ; 
 int MLXSW_SP_SB_TC_COUNT ; 
 int /*<<< orphan*/  bulk_list ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 size_t mlxsw_core_max_ports (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_reg_sbsr_egress_port_mask_set (char*,size_t,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbsr_ingress_port_mask_set (char*,size_t,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbsr_pack (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbsr_pg_buff_mask_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sbsr_tclass_mask_set (char*,int,int) ; 
 int mlxsw_reg_trans_bulk_wait (int /*<<< orphan*/ *) ; 
 int mlxsw_reg_trans_query (struct mlxsw_core*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_sb_pm_occ_clear (struct mlxsw_sp*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbsr ; 

int mlxsw_sp_sb_occ_max_clear(struct mlxsw_core *mlxsw_core,
			      unsigned int sb_index)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	LIST_HEAD(bulk_list);
	char *sbsr_pl;
	unsigned int masked_count;
	u8 local_port = 0;
	int i;
	int err;
	int err2;

	sbsr_pl = kmalloc(MLXSW_REG_SBSR_LEN, GFP_KERNEL);
	if (!sbsr_pl)
		return -ENOMEM;

next_batch:
	local_port++;
	masked_count = 0;
	mlxsw_reg_sbsr_pack(sbsr_pl, true);
	for (i = 0; i < MLXSW_SP_SB_TC_COUNT; i++) {
		mlxsw_reg_sbsr_pg_buff_mask_set(sbsr_pl, i, 1);
		mlxsw_reg_sbsr_tclass_mask_set(sbsr_pl, i, 1);
	}
	for (; local_port < mlxsw_core_max_ports(mlxsw_core); local_port++) {
		if (!mlxsw_sp->ports[local_port])
			continue;
		mlxsw_reg_sbsr_ingress_port_mask_set(sbsr_pl, local_port, 1);
		mlxsw_reg_sbsr_egress_port_mask_set(sbsr_pl, local_port, 1);
		for (i = 0; i < MLXSW_SP_SB_POOL_COUNT; i++) {
			err = mlxsw_sp_sb_pm_occ_clear(mlxsw_sp, local_port, i,
						       MLXSW_REG_SBXX_DIR_INGRESS,
						       &bulk_list);
			if (err)
				goto out;
			err = mlxsw_sp_sb_pm_occ_clear(mlxsw_sp, local_port, i,
						       MLXSW_REG_SBXX_DIR_EGRESS,
						       &bulk_list);
			if (err)
				goto out;
		}
		if (++masked_count == MASKED_COUNT_MAX)
			goto do_query;
	}

do_query:
	err = mlxsw_reg_trans_query(mlxsw_core, MLXSW_REG(sbsr), sbsr_pl,
				    &bulk_list, NULL, 0);
	if (err)
		goto out;
	if (local_port < mlxsw_core_max_ports(mlxsw_core))
		goto next_batch;

out:
	err2 = mlxsw_reg_trans_bulk_wait(&bulk_list);
	if (!err)
		err = err2;
	kfree(sbsr_pl);
	return err;
}