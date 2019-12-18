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
struct mlxsw_sp_ipip_entry {int /*<<< orphan*/  ol_dev; int /*<<< orphan*/  ol_lb; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr4; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_ipip_fib_entry_op_gre4_ralue (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_ipip_fib_entry_op_gre4_rtdp (struct mlxsw_sp*,int /*<<< orphan*/ ,struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_lb_ul_vr_id (int /*<<< orphan*/ ) ; 
 TYPE_1__ mlxsw_sp_ipip_netdev_saddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_ipip_fib_entry_op_gre4(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_ipip_entry *ipip_entry,
					enum mlxsw_reg_ralue_op op,
					u32 tunnel_index)
{
	u16 ul_vr_id = mlxsw_sp_ipip_lb_ul_vr_id(ipip_entry->ol_lb);
	__be32 dip;
	int err;

	err = mlxsw_sp_ipip_fib_entry_op_gre4_rtdp(mlxsw_sp, tunnel_index,
						   ipip_entry);
	if (err)
		return err;

	dip = mlxsw_sp_ipip_netdev_saddr(MLXSW_SP_L3_PROTO_IPV4,
					 ipip_entry->ol_dev).addr4;
	return mlxsw_sp_ipip_fib_entry_op_gre4_ralue(mlxsw_sp, be32_to_cpu(dip),
						     32, ul_vr_id, op,
						     tunnel_index);
}