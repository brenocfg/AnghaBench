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
 int /*<<< orphan*/  MLXSW_REG_MLCR_DURATION_MAX ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlcr ; 
 int /*<<< orphan*/  mlxsw_reg_mlcr_beacon_duration_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mlcr_local_port_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_mlcr_pack(char *payload, u8 local_port,
				       bool active)
{
	MLXSW_REG_ZERO(mlcr, payload);
	mlxsw_reg_mlcr_local_port_set(payload, local_port);
	mlxsw_reg_mlcr_beacon_duration_set(payload, active ?
					   MLXSW_REG_MLCR_DURATION_MAX : 0);
}