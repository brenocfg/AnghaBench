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
struct mlxsw_reg_info {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_EMAD_TLV_TYPE_REG ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mlxsw_emad_reg_tlv_len_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_emad_reg_tlv_type_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_emad_pack_reg_tlv(char *reg_tlv,
				    const struct mlxsw_reg_info *reg,
				    char *payload)
{
	mlxsw_emad_reg_tlv_type_set(reg_tlv, MLXSW_EMAD_TLV_TYPE_REG);
	mlxsw_emad_reg_tlv_len_set(reg_tlv, reg->len / sizeof(u32) + 1);
	memcpy(reg_tlv + sizeof(u32), payload, reg->len);
}