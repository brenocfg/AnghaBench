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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppad_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ppad_single_base_mac_set (char*,int) ; 
 int /*<<< orphan*/  ppad ; 

__attribute__((used)) static inline void mlxsw_reg_ppad_pack(char *payload, bool single_base_mac,
				       u8 local_port)
{
	MLXSW_REG_ZERO(ppad, payload);
	mlxsw_reg_ppad_single_base_mac_set(payload, !!single_base_mac);
	mlxsw_reg_ppad_local_port_set(payload, local_port);
}