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
typedef  int u8 ;
typedef  int u16 ;
struct fm10k_vf_info {int vf_flags; int glort; } ;
struct TYPE_2__ {int dglort_map; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int FM10K_DGLORTMAP_NONE ; 
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int FM10K_VF_FLAG_NONE_CAPABLE ; 
 int /*<<< orphan*/  fm10k_glort_valid_pf (struct fm10k_hw*,int) ; 

__attribute__((used)) static s32 fm10k_iov_set_lport_pf(struct fm10k_hw *hw,
				  struct fm10k_vf_info *vf_info,
				  u16 lport_idx, u8 flags)
{
	u16 glort = (hw->mac.dglort_map + lport_idx) & FM10K_DGLORTMAP_NONE;

	/* if glort is not valid return error */
	if (!fm10k_glort_valid_pf(hw, glort))
		return FM10K_ERR_PARAM;

	vf_info->vf_flags = flags | FM10K_VF_FLAG_NONE_CAPABLE;
	vf_info->glort = glort;

	return 0;
}