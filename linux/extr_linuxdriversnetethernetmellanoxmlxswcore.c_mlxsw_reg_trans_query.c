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
struct mlxsw_reg_info {int dummy; } ;
struct mlxsw_core {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  mlxsw_reg_trans_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_CORE_REG_ACCESS_TYPE_QUERY ; 
 int mlxsw_core_reg_access_emad (struct mlxsw_core*,struct mlxsw_reg_info const*,char*,int /*<<< orphan*/ ,struct list_head*,int /*<<< orphan*/ *,unsigned long) ; 

int mlxsw_reg_trans_query(struct mlxsw_core *mlxsw_core,
			  const struct mlxsw_reg_info *reg, char *payload,
			  struct list_head *bulk_list,
			  mlxsw_reg_trans_cb_t *cb, unsigned long cb_priv)
{
	return mlxsw_core_reg_access_emad(mlxsw_core, reg, payload,
					  MLXSW_CORE_REG_ACCESS_TYPE_QUERY,
					  bulk_list, cb, cb_priv);
}