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
 int FM10K_TLV_FLAGS_MSG ; 
 int FM10K_TLV_FLAGS_SHIFT ; 

s32 fm10k_tlv_msg_init(u32 *msg, u16 msg_id)
{
	/* verify pointer is not NULL */
	if (!msg)
		return FM10K_ERR_PARAM;

	*msg = (FM10K_TLV_FLAGS_MSG << FM10K_TLV_FLAGS_SHIFT) | msg_id;

	return 0;
}