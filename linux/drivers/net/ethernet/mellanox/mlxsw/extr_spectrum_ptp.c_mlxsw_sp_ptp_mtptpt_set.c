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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_mtptpt_trap_id { ____Placeholder_mlxsw_reg_mtptpt_trap_id } mlxsw_reg_mtptpt_trap_id ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MTPTPT_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_mtptptp_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtptpt ; 

__attribute__((used)) static int mlxsw_sp_ptp_mtptpt_set(struct mlxsw_sp *mlxsw_sp,
				   enum mlxsw_reg_mtptpt_trap_id trap_id,
				   u16 message_type)
{
	char mtptpt_pl[MLXSW_REG_MTPTPT_LEN];

	mlxsw_reg_mtptptp_pack(mtptpt_pl, trap_id, message_type);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mtptpt), mtptpt_pl);
}