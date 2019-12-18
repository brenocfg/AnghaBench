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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mgir_fw_info_extended_major_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgir_fw_info_extended_minor_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgir_fw_info_extended_sub_minor_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgir_fw_info_psid_memcpy_from (char*,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgir_hw_info_device_hw_revision_get (char*) ; 

__attribute__((used)) static inline void
mlxsw_reg_mgir_unpack(char *payload, u32 *hw_rev, char *fw_info_psid,
		      u32 *fw_major, u32 *fw_minor, u32 *fw_sub_minor)
{
	*hw_rev = mlxsw_reg_mgir_hw_info_device_hw_revision_get(payload);
	mlxsw_reg_mgir_fw_info_psid_memcpy_from(payload, fw_info_psid);
	*fw_major = mlxsw_reg_mgir_fw_info_extended_major_get(payload);
	*fw_minor = mlxsw_reg_mgir_fw_info_extended_minor_get(payload);
	*fw_sub_minor = mlxsw_reg_mgir_fw_info_extended_sub_minor_get(payload);
}