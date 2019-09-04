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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct SPU2_FMD {void* ctrl3; void* ctrl2; void* ctrl1; void* ctrl0; } ;
typedef  enum spu2_cipher_type { ____Placeholder_spu2_cipher_type } spu2_cipher_type ;
typedef  enum spu2_cipher_mode { ____Placeholder_spu2_cipher_mode } spu2_cipher_mode ;

/* Variables and functions */
 int SPU2_AAD1_LEN_SHIFT ; 
 int SPU2_AAD2_OFFSET_SHIFT ; 
 int SPU2_CIPH_KEY_LEN_SHIFT ; 
 int SPU2_CIPH_MODE_SHIFT ; 
 int SPU2_CIPH_TYPE_SHIFT ; 
 int SPU2_IV_LEN_SHIFT ; 
 int SPU2_PL_OFFSET_SHIFT ; 
 int SPU2_RETURN_MD_SHIFT ; 
 int SPU2_RETURN_PAY ; 
 scalar_t__ SPU2_RET_FMD_ONLY ; 
 void* cpu_to_le64 (int) ; 

__attribute__((used)) static int spu2_fmd_init(struct SPU2_FMD *fmd,
			 enum spu2_cipher_type spu2_type,
			 enum spu2_cipher_mode spu2_mode,
			 u32 cipher_key_len, u32 cipher_iv_len)
{
	u64 ctrl0;
	u64 ctrl1;
	u64 ctrl2;
	u64 ctrl3;
	u32 aad1_offset;
	u32 aad2_offset;
	u16 aad1_len = 0;
	u64 payload_offset;

	ctrl0 = (spu2_type << SPU2_CIPH_TYPE_SHIFT) |
	    (spu2_mode << SPU2_CIPH_MODE_SHIFT);

	ctrl1 = (cipher_key_len << SPU2_CIPH_KEY_LEN_SHIFT) |
	    ((u64)cipher_iv_len << SPU2_IV_LEN_SHIFT) |
	    ((u64)SPU2_RET_FMD_ONLY << SPU2_RETURN_MD_SHIFT) | SPU2_RETURN_PAY;

	/*
	 * AAD1 offset is from start of FD. FD length is always 0 for this
	 * driver. So AAD1_offset is always 0.
	 */
	aad1_offset = 0;
	aad2_offset = aad1_offset;
	payload_offset = 0;
	ctrl2 = aad1_offset |
	    (aad1_len << SPU2_AAD1_LEN_SHIFT) |
	    (aad2_offset << SPU2_AAD2_OFFSET_SHIFT) |
	    (payload_offset << SPU2_PL_OFFSET_SHIFT);

	ctrl3 = 0;

	fmd->ctrl0 = cpu_to_le64(ctrl0);
	fmd->ctrl1 = cpu_to_le64(ctrl1);
	fmd->ctrl2 = cpu_to_le64(ctrl2);
	fmd->ctrl3 = cpu_to_le64(ctrl3);

	return 0;
}