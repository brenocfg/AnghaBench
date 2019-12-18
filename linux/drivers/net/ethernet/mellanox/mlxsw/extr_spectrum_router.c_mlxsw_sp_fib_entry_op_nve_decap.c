#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tunnel_index; } ;
struct mlxsw_sp_fib_entry {TYPE_1__ decap; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RALUE_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_act_ip2me_tun_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_ralue_pack (char*,struct mlxsw_sp_fib_entry*,int) ; 
 int /*<<< orphan*/  ralue ; 

__attribute__((used)) static int mlxsw_sp_fib_entry_op_nve_decap(struct mlxsw_sp *mlxsw_sp,
					   struct mlxsw_sp_fib_entry *fib_entry,
					   enum mlxsw_reg_ralue_op op)
{
	char ralue_pl[MLXSW_REG_RALUE_LEN];

	mlxsw_sp_fib_entry_ralue_pack(ralue_pl, fib_entry, op);
	mlxsw_reg_ralue_act_ip2me_tun_pack(ralue_pl,
					   fib_entry->decap.tunnel_index);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ralue), ralue_pl);
}