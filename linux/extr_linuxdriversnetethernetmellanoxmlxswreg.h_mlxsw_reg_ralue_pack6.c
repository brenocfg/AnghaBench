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
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ralue_dip6_memcpy_to (char*,void const*) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_pack (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_ralue_pack6(char *payload,
					 enum mlxsw_reg_ralxx_protocol protocol,
					 enum mlxsw_reg_ralue_op op,
					 u16 virtual_router, u8 prefix_len,
					 const void *dip)
{
	mlxsw_reg_ralue_pack(payload, protocol, op, virtual_router, prefix_len);
	mlxsw_reg_ralue_dip6_memcpy_to(payload, dip);
}