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
typedef  enum mlxsw_reg_prcr_op { ____Placeholder_mlxsw_reg_prcr_op } mlxsw_reg_prcr_op ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_dest_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_dest_tcam_region_info_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_offset_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_op_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_tcam_region_info_memcpy_to (char*,char const*) ; 
 int /*<<< orphan*/  prcr ; 

__attribute__((used)) static inline void mlxsw_reg_prcr_pack(char *payload, enum mlxsw_reg_prcr_op op,
				       const char *src_tcam_region_info,
				       u16 src_offset,
				       const char *dest_tcam_region_info,
				       u16 dest_offset, u16 size)
{
	MLXSW_REG_ZERO(prcr, payload);
	mlxsw_reg_prcr_op_set(payload, op);
	mlxsw_reg_prcr_offset_set(payload, src_offset);
	mlxsw_reg_prcr_size_set(payload, size);
	mlxsw_reg_prcr_tcam_region_info_memcpy_to(payload,
						  src_tcam_region_info);
	mlxsw_reg_prcr_dest_offset_set(payload, dest_offset);
	mlxsw_reg_prcr_dest_tcam_region_info_memcpy_to(payload,
						       dest_tcam_region_info);
}