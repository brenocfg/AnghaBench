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
struct fm10k_mbx_info {int dummy; } ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_NOT_IMPLEMENTED ; 

s32 fm10k_tlv_msg_error(struct fm10k_hw *hw, u32 **results,
			struct fm10k_mbx_info *mbx)
{
	return FM10K_NOT_IMPLEMENTED;
}