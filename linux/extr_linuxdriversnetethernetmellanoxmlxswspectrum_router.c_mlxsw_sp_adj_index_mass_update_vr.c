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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_fib {TYPE_1__* vr; scalar_t__ proto; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RALEU_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_raleu_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  raleu ; 

__attribute__((used)) static int mlxsw_sp_adj_index_mass_update_vr(struct mlxsw_sp *mlxsw_sp,
					     const struct mlxsw_sp_fib *fib,
					     u32 adj_index, u16 ecmp_size,
					     u32 new_adj_index,
					     u16 new_ecmp_size)
{
	char raleu_pl[MLXSW_REG_RALEU_LEN];

	mlxsw_reg_raleu_pack(raleu_pl,
			     (enum mlxsw_reg_ralxx_protocol) fib->proto,
			     fib->vr->id, adj_index, ecmp_size, new_adj_index,
			     new_ecmp_size);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(raleu), raleu_pl);
}