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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_link_width_cap_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_link_width_oper_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_proto_cap_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_proto_oper_get (char*) ; 

__attribute__((used)) static inline void mlxsw_reg_ptys_ib_unpack(char *payload, u16 *p_ib_proto_cap,
					    u16 *p_ib_link_width_cap,
					    u16 *p_ib_proto_oper,
					    u16 *p_ib_link_width_oper)
{
	if (p_ib_proto_cap)
		*p_ib_proto_cap = mlxsw_reg_ptys_ib_proto_cap_get(payload);
	if (p_ib_link_width_cap)
		*p_ib_link_width_cap =
			mlxsw_reg_ptys_ib_link_width_cap_get(payload);
	if (p_ib_proto_oper)
		*p_ib_proto_oper = mlxsw_reg_ptys_ib_proto_oper_get(payload);
	if (p_ib_link_width_oper)
		*p_ib_link_width_oper =
			mlxsw_reg_ptys_ib_link_width_oper_get(payload);
}