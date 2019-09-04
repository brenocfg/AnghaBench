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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_IEDR_LEN ; 
 int /*<<< orphan*/  iedr ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_iedr_pack (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_iedr_rec_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_sp2_kvdl_rec_del(struct mlxsw_sp *mlxsw_sp, u8 res_type,
				  u16 size, u32 kvdl_index)
{
	char *iedr_pl;
	int err;

	iedr_pl = kmalloc(MLXSW_REG_IEDR_LEN, GFP_KERNEL);
	if (!iedr_pl)
		return -ENOMEM;

	mlxsw_reg_iedr_pack(iedr_pl);
	mlxsw_reg_iedr_rec_pack(iedr_pl, 0, res_type, size, kvdl_index);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(iedr), iedr_pl);
	kfree(iedr_pl);
	return err;
}