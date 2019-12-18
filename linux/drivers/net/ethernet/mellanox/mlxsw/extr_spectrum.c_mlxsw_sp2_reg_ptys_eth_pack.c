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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ptys_ext_eth_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mlxsw_sp2_reg_ptys_eth_pack(struct mlxsw_sp *mlxsw_sp, char *payload,
			    u8 local_port, u32 proto_admin,
			    bool autoneg)
{
	mlxsw_reg_ptys_ext_eth_pack(payload, local_port, proto_admin, autoneg);
}