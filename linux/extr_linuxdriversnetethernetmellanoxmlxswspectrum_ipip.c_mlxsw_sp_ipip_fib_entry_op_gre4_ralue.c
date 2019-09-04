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
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RALUE_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RALXX_PROTOCOL_IPV4 ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_act_ip2me_tun_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_pack4 (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ralue ; 

__attribute__((used)) static int
mlxsw_sp_ipip_fib_entry_op_gre4_ralue(struct mlxsw_sp *mlxsw_sp,
				      u32 dip, u8 prefix_len, u16 ul_vr_id,
				      enum mlxsw_reg_ralue_op op,
				      u32 tunnel_index)
{
	char ralue_pl[MLXSW_REG_RALUE_LEN];

	mlxsw_reg_ralue_pack4(ralue_pl, MLXSW_REG_RALXX_PROTOCOL_IPV4, op,
			      ul_vr_id, prefix_len, dip);
	mlxsw_reg_ralue_act_ip2me_tun_pack(ralue_pl, tunnel_index);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ralue), ralue_pl);
}