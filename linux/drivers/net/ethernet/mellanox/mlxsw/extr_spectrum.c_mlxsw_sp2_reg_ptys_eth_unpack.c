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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ptys_ext_eth_unpack (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp2_reg_ptys_eth_unpack(struct mlxsw_sp *mlxsw_sp, char *payload,
			      u32 *p_eth_proto_cap, u32 *p_eth_proto_admin,
			      u32 *p_eth_proto_oper)
{
	mlxsw_reg_ptys_ext_eth_unpack(payload, p_eth_proto_cap,
				      p_eth_proto_admin, p_eth_proto_oper);
}