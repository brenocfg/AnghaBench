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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_PTYS_PROTO_MASK_IB ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_link_width_admin_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_proto_admin_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_proto_mask_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys ; 

__attribute__((used)) static inline void mlxsw_reg_ptys_ib_pack(char *payload, u8 local_port,
					  u16 proto_admin, u16 link_width)
{
	MLXSW_REG_ZERO(ptys, payload);
	mlxsw_reg_ptys_local_port_set(payload, local_port);
	mlxsw_reg_ptys_proto_mask_set(payload, MLXSW_REG_PTYS_PROTO_MASK_IB);
	mlxsw_reg_ptys_ib_proto_admin_set(payload, proto_admin);
	mlxsw_reg_ptys_ib_link_width_admin_set(payload, link_width);
}