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
 int /*<<< orphan*/  mlxsw_reg_pacl_acl_id_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pacl_tcam_region_info_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_pacl_v_set (char*,int) ; 
 int /*<<< orphan*/  pacl ; 

__attribute__((used)) static inline void mlxsw_reg_pacl_pack(char *payload, u16 acl_id,
				       bool valid, const char *tcam_region_info)
{
	MLXSW_REG_ZERO(pacl, payload);
	mlxsw_reg_pacl_acl_id_set(payload, acl_id);
	mlxsw_reg_pacl_v_set(payload, valid);
	mlxsw_reg_pacl_tcam_region_info_memcpy_to(payload, tcam_region_info);
}