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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 size_t FM10K_TLV_LEN_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 

s32 fm10k_tlv_attr_get_le_struct(u32 *attr, void *le_struct, u32 len)
{
	__le32 *le32_ptr = (__le32 *)le_struct;
	u32 i;

	/* verify pointers are not NULL */
	if (!le_struct || !attr)
		return FM10K_ERR_PARAM;

	if ((*attr >> FM10K_TLV_LEN_SHIFT) != len)
		return FM10K_ERR_PARAM;

	attr++;

	for (i = 0; len; i++, len -= 4)
		le32_ptr[i] = cpu_to_le32(attr[i]);

	return 0;
}