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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_flood_table {int /*<<< orphan*/  table_type; int /*<<< orphan*/  table_index; } ;
struct mlxsw_sp_fid_ops {int /*<<< orphan*/  (* flood_index ) (struct mlxsw_sp_fid*) ;} ;
struct mlxsw_sp_fid_family {TYPE_1__* mlxsw_sp; int /*<<< orphan*/  flood_tables; struct mlxsw_sp_fid_ops* ops; } ;
struct mlxsw_sp_fid {struct mlxsw_sp_fid_family* fid_family; } ;
typedef  enum mlxsw_sp_flood_type { ____Placeholder_mlxsw_sp_flood_type } mlxsw_sp_flood_type ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_SFTR_LEN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sftr_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_flood_table* mlxsw_sp_fid_flood_table_lookup (struct mlxsw_sp_fid*,int) ; 
 int /*<<< orphan*/  sftr ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_fid*) ; 

int mlxsw_sp_fid_flood_set(struct mlxsw_sp_fid *fid,
			   enum mlxsw_sp_flood_type packet_type, u8 local_port,
			   bool member)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;
	const struct mlxsw_sp_fid_ops *ops = fid_family->ops;
	const struct mlxsw_sp_flood_table *flood_table;
	char *sftr_pl;
	int err;

	if (WARN_ON(!fid_family->flood_tables || !ops->flood_index))
		return -EINVAL;

	flood_table = mlxsw_sp_fid_flood_table_lookup(fid, packet_type);
	if (!flood_table)
		return -ESRCH;

	sftr_pl = kmalloc(MLXSW_REG_SFTR_LEN, GFP_KERNEL);
	if (!sftr_pl)
		return -ENOMEM;

	mlxsw_reg_sftr_pack(sftr_pl, flood_table->table_index,
			    ops->flood_index(fid), flood_table->table_type, 1,
			    local_port, member);
	err = mlxsw_reg_write(fid_family->mlxsw_sp->core, MLXSW_REG(sftr),
			      sftr_pl);
	kfree(sftr_pl);
	return err;
}