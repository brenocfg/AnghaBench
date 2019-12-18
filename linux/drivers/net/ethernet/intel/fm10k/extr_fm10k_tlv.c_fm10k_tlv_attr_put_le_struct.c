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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 size_t FM10K_TLV_DWORD_LEN (int) ; 
 int FM10K_TLV_HDR_LEN ; 
 scalar_t__ FM10K_TLV_LEN_ALIGN (int) ; 
 int FM10K_TLV_LEN_SHIFT ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 

s32 fm10k_tlv_attr_put_le_struct(u32 *msg, u16 attr_id,
				 const void *le_struct, u32 len)
{
	const __le32 *le32_ptr = (const __le32 *)le_struct;
	u32 *attr;
	u32 i;

	/* verify non-null msg and len is in 32 bit words */
	if (!msg || !len || (len % 4))
		return FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	/* copy le32 structure into host byte order at 32b boundaries */
	for (i = 0; i < (len / 4); i++)
		attr[i + 1] = le32_to_cpu(le32_ptr[i]);

	/* record attribute header, update message length */
	len <<= FM10K_TLV_LEN_SHIFT;
	attr[0] = len | attr_id;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	return 0;
}