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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RITR_LEN ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_if_vrrp_id_ipv4_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_if_vrrp_id_ipv6_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_rif_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mlxsw_sp_rif_macvlan_is_vrrp4 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_macvlan_is_vrrp6 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ritr ; 

__attribute__((used)) static int mlxsw_sp_rif_vrrp_op(struct mlxsw_sp *mlxsw_sp, u16 rif_index,
				const u8 *mac, bool adding)
{
	char ritr_pl[MLXSW_REG_RITR_LEN];
	u8 vrrp_id = adding ? mac[5] : 0;
	int err;

	if (!mlxsw_sp_rif_macvlan_is_vrrp4(mac) &&
	    !mlxsw_sp_rif_macvlan_is_vrrp6(mac))
		return 0;

	mlxsw_reg_ritr_rif_pack(ritr_pl, rif_index);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
	if (err)
		return err;

	if (mlxsw_sp_rif_macvlan_is_vrrp4(mac))
		mlxsw_reg_ritr_if_vrrp_id_ipv4_set(ritr_pl, vrrp_id);
	else
		mlxsw_reg_ritr_if_vrrp_id_ipv6_set(ritr_pl, vrrp_id);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
}