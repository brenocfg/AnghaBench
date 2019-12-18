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

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 size_t FM10K_TLV_DWORD_LEN (int) ; 
 int FM10K_TLV_HDR_LEN ; 
 scalar_t__ FM10K_TLV_LEN_ALIGN (int) ; 
 int FM10K_TLV_LEN_SHIFT ; 

__attribute__((used)) static s32 fm10k_tlv_attr_put_null_string(u32 *msg, u16 attr_id,
					  const unsigned char *string)
{
	u32 attr_data = 0, len = 0;
	u32 *attr;

	/* verify pointers are not NULL */
	if (!string || !msg)
		return FM10K_ERR_PARAM;

	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];

	/* copy string into local variable and then write to msg */
	do {
		/* write data to message */
		if (len && !(len % 4)) {
			attr[len / 4] = attr_data;
			attr_data = 0;
		}

		/* record character to offset location */
		attr_data |= (u32)(*string) << (8 * (len % 4));
		len++;

		/* test for NULL and then increment */
	} while (*(string++));

	/* write last piece of data to message */
	attr[(len + 3) / 4] = attr_data;

	/* record attribute header, update message length */
	len <<= FM10K_TLV_LEN_SHIFT;
	attr[0] = len | attr_id;

	/* add header length to length */
	len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
	*msg += FM10K_TLV_LEN_ALIGN(len);

	return 0;
}