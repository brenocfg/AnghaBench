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
 int /*<<< orphan*/  MLXSW_REG_SPVMLR_LEN ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_spvmlr_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spvmlr ; 

int mlxsw_sp_port_vid_learning_set(struct mlxsw_sp_port *mlxsw_sp_port, u16 vid,
				   bool learn_enable)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char *spvmlr_pl;
	int err;

	spvmlr_pl = kmalloc(MLXSW_REG_SPVMLR_LEN, GFP_KERNEL);
	if (!spvmlr_pl)
		return -ENOMEM;
	mlxsw_reg_spvmlr_pack(spvmlr_pl, mlxsw_sp_port->local_port, vid, vid,
			      learn_enable);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(spvmlr), spvmlr_pl);
	kfree(spvmlr_pl);
	return err;
}