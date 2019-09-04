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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_SMID_LEN ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_smid_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smid ; 

__attribute__((used)) static int mlxsw_sp_port_smid_set(struct mlxsw_sp_port *mlxsw_sp_port,
				  u16 mid_idx, bool add)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char *smid_pl;
	int err;

	smid_pl = kmalloc(MLXSW_REG_SMID_LEN, GFP_KERNEL);
	if (!smid_pl)
		return -ENOMEM;

	mlxsw_reg_smid_pack(smid_pl, mid_idx, mlxsw_sp_port->local_port, add);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(smid), smid_pl);
	kfree(smid_pl);
	return err;
}