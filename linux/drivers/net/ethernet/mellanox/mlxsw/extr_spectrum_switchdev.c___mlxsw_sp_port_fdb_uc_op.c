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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_sfd_rec_policy { ____Placeholder_mlxsw_reg_sfd_rec_policy } mlxsw_reg_sfd_rec_policy ;
typedef  enum mlxsw_reg_sfd_rec_action { ____Placeholder_mlxsw_reg_sfd_rec_action } mlxsw_reg_sfd_rec_action ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_SFD_LEN ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_reg_sfd_num_rec_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfd_uc_pack (char*,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_sfd_op (int) ; 
 int /*<<< orphan*/  sfd ; 

__attribute__((used)) static int __mlxsw_sp_port_fdb_uc_op(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				     const char *mac, u16 fid, bool adding,
				     enum mlxsw_reg_sfd_rec_action action,
				     enum mlxsw_reg_sfd_rec_policy policy)
{
	char *sfd_pl;
	u8 num_rec;
	int err;

	sfd_pl = kmalloc(MLXSW_REG_SFD_LEN, GFP_KERNEL);
	if (!sfd_pl)
		return -ENOMEM;

	mlxsw_reg_sfd_pack(sfd_pl, mlxsw_sp_sfd_op(adding), 0);
	mlxsw_reg_sfd_uc_pack(sfd_pl, 0, policy, mac, fid, action, local_port);
	num_rec = mlxsw_reg_sfd_num_rec_get(sfd_pl);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfd), sfd_pl);
	if (err)
		goto out;

	if (num_rec != mlxsw_reg_sfd_num_rec_get(sfd_pl))
		err = -EBUSY;

out:
	kfree(sfd_pl);
	return err;
}