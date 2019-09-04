#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fm10k_vf_info {int /*<<< orphan*/  vf_idx; } ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* assign_int_moderator ) (struct fm10k_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ iov; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

s32 fm10k_iov_msg_msix_pf(struct fm10k_hw *hw, u32 **results,
			  struct fm10k_mbx_info *mbx)
{
	struct fm10k_vf_info *vf_info = (struct fm10k_vf_info *)mbx;
	u8 vf_idx = vf_info->vf_idx;

	return hw->iov.ops.assign_int_moderator(hw, vf_idx);
}