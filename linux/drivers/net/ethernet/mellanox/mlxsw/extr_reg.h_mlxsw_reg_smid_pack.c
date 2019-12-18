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
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_smid_mid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_smid_port_mask_set (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_smid_port_set (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_smid_swid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smid ; 

__attribute__((used)) static inline void mlxsw_reg_smid_pack(char *payload, u16 mid,
				       u8 port, bool set)
{
	MLXSW_REG_ZERO(smid, payload);
	mlxsw_reg_smid_swid_set(payload, 0);
	mlxsw_reg_smid_mid_set(payload, mid);
	mlxsw_reg_smid_port_set(payload, port, set);
	mlxsw_reg_smid_port_mask_set(payload, port, 1);
}