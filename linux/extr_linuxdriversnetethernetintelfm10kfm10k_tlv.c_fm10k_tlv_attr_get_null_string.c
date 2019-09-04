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
typedef  unsigned char u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 size_t FM10K_TLV_LEN_SHIFT ; 

__attribute__((used)) static s32 fm10k_tlv_attr_get_null_string(u32 *attr, unsigned char *string)
{
	u32 len;

	/* verify pointers are not NULL */
	if (!string || !attr)
		return FM10K_ERR_PARAM;

	len = *attr >> FM10K_TLV_LEN_SHIFT;
	attr++;

	while (len--)
		string[len] = (u8)(attr[len / 4] >> (8 * (len % 4)));

	return 0;
}