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
 int /*<<< orphan*/  mlxsw_reg_tndem_eip_ecn_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tndem_overlay_ecn_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tndem_trap_en_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tndem_trap_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tndem_underlay_ecn_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tndem ; 

__attribute__((used)) static inline void mlxsw_reg_tndem_pack(char *payload, u8 underlay_ecn,
					u8 overlay_ecn, u8 ecn, bool trap_en,
					u16 trap_id)
{
	MLXSW_REG_ZERO(tndem, payload);
	mlxsw_reg_tndem_underlay_ecn_set(payload, underlay_ecn);
	mlxsw_reg_tndem_overlay_ecn_set(payload, overlay_ecn);
	mlxsw_reg_tndem_eip_ecn_set(payload, ecn);
	mlxsw_reg_tndem_trap_en_set(payload, trap_en);
	mlxsw_reg_tndem_trap_id_set(payload, trap_id);
}