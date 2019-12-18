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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbs_pbs_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppbs_system_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppbs ; 

__attribute__((used)) static inline void mlxsw_reg_ppbs_pack(char *payload, u32 pbs_ptr,
				       u16 system_port)
{
	MLXSW_REG_ZERO(ppbs, payload);
	mlxsw_reg_ppbs_pbs_ptr_set(payload, pbs_ptr);
	mlxsw_reg_ppbs_system_port_set(payload, system_port);
}