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
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_percr_atcam_ignore_prune_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_percr_bf_bypass_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_percr_ctcam_ignore_prune_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_percr_region_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percr ; 

__attribute__((used)) static inline void mlxsw_reg_percr_pack(char *payload, u16 region_id)
{
	MLXSW_REG_ZERO(percr, payload);
	mlxsw_reg_percr_region_id_set(payload, region_id);
	mlxsw_reg_percr_atcam_ignore_prune_set(payload, false);
	mlxsw_reg_percr_ctcam_ignore_prune_set(payload, false);
	mlxsw_reg_percr_bf_bypass_set(payload, false);
}