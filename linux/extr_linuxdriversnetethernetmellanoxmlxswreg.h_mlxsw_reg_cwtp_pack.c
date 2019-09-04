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
 int MLXSW_REG_CWTP_MAX_PROFILE ; 
 int /*<<< orphan*/  MLXSW_REG_CWTP_MIN_VALUE ; 
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cwtp ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_local_port_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_profile_max_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_profile_min_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_traffic_class_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_cwtp_pack(char *payload, u8 local_port,
				       u8 traffic_class)
{
	int i;

	MLXSW_REG_ZERO(cwtp, payload);
	mlxsw_reg_cwtp_local_port_set(payload, local_port);
	mlxsw_reg_cwtp_traffic_class_set(payload, traffic_class);

	for (i = 0; i <= MLXSW_REG_CWTP_MAX_PROFILE; i++) {
		mlxsw_reg_cwtp_profile_min_set(payload, i,
					       MLXSW_REG_CWTP_MIN_VALUE);
		mlxsw_reg_cwtp_profile_max_set(payload, i,
					       MLXSW_REG_CWTP_MIN_VALUE);
	}
}