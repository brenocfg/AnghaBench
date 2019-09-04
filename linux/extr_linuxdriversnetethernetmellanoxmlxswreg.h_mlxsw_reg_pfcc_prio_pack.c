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
 int /*<<< orphan*/  MLXSW_REG_PFCC_ALL_PRIO ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_pfcrx_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_pfctx_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_prio_mask_rx_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_prio_mask_tx_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_pfcc_prio_pack(char *payload, u8 pfc_en)
{
	mlxsw_reg_pfcc_prio_mask_tx_set(payload, MLXSW_REG_PFCC_ALL_PRIO);
	mlxsw_reg_pfcc_prio_mask_rx_set(payload, MLXSW_REG_PFCC_ALL_PRIO);
	mlxsw_reg_pfcc_pfctx_set(payload, pfc_en);
	mlxsw_reg_pfcc_pfcrx_set(payload, pfc_en);
}