#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dglort_map; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_DGLORTMAP_NONE ; 
 int /*<<< orphan*/  FM10K_DGLORTMAP_ZERO ; 
 size_t FM10K_LPORT_STATE_MSG_READY ; 

s32 fm10k_msg_lport_state_vf(struct fm10k_hw *hw, u32 **results,
			     struct fm10k_mbx_info *mbx)
{
	hw->mac.dglort_map = !results[FM10K_LPORT_STATE_MSG_READY] ?
			     FM10K_DGLORTMAP_NONE : FM10K_DGLORTMAP_ZERO;

	return 0;
}