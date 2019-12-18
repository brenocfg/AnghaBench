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
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 size_t FM10K_TLV_DWORD_LEN (int) ; 
 int FM10K_TLV_HDR_LEN ; 
 scalar_t__ FM10K_TLV_LEN_ALIGN (int) ; 
 int FM10K_TLV_LEN_SHIFT ; 

s32 fm10k_tlv_attr_put_value(u32 *msg, u16 attr_id, s64 value, u32 len)
{
	u32 *attr;

	/* verify non-null msg and len is 1, 2, 4, or 8 */
	if (!msg || !len || len > 8 || (len & (len - 1)))
		return FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	if (len < 4) {
		attr[1] = (u32)value & (BIT(8 * len) - 1);
	} else {
		attr[1] = (u32)value;
		if (len > 4)
			attr[2] = (u32)(value >> 32);
	}

	/* record attribute header, update message length */
	len <<= FM10K_TLV_LEN_SHIFT;
	attr[0] = len | attr_id;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	return 0;
}