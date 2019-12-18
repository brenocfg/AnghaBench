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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_CWTP_PROFILE_TO_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_profile_max_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_profile_min_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_cwtp_profile_percent_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlxsw_reg_cwtp_profile_pack(char *payload, u8 profile, u32 min, u32 max,
			    u32 probability)
{
	u8 index = MLXSW_REG_CWTP_PROFILE_TO_INDEX(profile);

	mlxsw_reg_cwtp_profile_min_set(payload, index, min);
	mlxsw_reg_cwtp_profile_max_set(payload, index, max);
	mlxsw_reg_cwtp_profile_percent_set(payload, index, probability);
}