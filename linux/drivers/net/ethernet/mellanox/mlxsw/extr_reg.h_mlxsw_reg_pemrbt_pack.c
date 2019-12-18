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
typedef  enum mlxsw_reg_pemrbt_protocol { ____Placeholder_mlxsw_reg_pemrbt_protocol } mlxsw_reg_pemrbt_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_pemrbt_group_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pemrbt_protocol_set (char*,int) ; 
 int /*<<< orphan*/  pemrbt ; 

__attribute__((used)) static inline void
mlxsw_reg_pemrbt_pack(char *payload, enum mlxsw_reg_pemrbt_protocol protocol,
		      u16 group_id)
{
	MLXSW_REG_ZERO(pemrbt, payload);
	mlxsw_reg_pemrbt_protocol_set(payload, protocol);
	mlxsw_reg_pemrbt_group_id_set(payload, group_id);
}