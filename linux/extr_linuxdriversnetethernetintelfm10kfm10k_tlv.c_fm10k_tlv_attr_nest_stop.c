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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 size_t FM10K_TLV_DWORD_LEN (int) ; 
 int FM10K_TLV_HDR_LEN ; 
 int FM10K_TLV_LEN_SHIFT ; 

__attribute__((used)) static s32 fm10k_tlv_attr_nest_stop(u32 *msg)
{
	u32 *attr;
	u32 len;

	/* verify pointer is not NULL */
	if (!msg)
		return FM10K_ERR_PARAM;

	/* locate the nested header and retrieve its length */
	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];
	len = (attr[0] >> FM10K_TLV_LEN_SHIFT) << FM10K_TLV_LEN_SHIFT;

	/* only include nest if data was added to it */
	if (len) {
		len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
		*msg += len;
	}

	return 0;
}