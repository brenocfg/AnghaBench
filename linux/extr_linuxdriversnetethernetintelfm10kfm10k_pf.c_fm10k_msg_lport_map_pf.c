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
typedef  int u16 ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dglort_map; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int FM10K_DGLORTMAP_NONE ; 
 scalar_t__ FM10K_ERR_PARAM ; 
 int FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FM10K_PF_ATTR_ID_LPORT_MAP ; 
 int /*<<< orphan*/  LPORT_MAP_GLORT ; 
 int /*<<< orphan*/  LPORT_MAP_MASK ; 
 scalar_t__ fm10k_tlv_attr_get_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

s32 fm10k_msg_lport_map_pf(struct fm10k_hw *hw, u32 **results,
			   struct fm10k_mbx_info *mbx)
{
	u16 glort, mask;
	u32 dglort_map;
	s32 err;

	err = fm10k_tlv_attr_get_u32(results[FM10K_PF_ATTR_ID_LPORT_MAP],
				     &dglort_map);
	if (err)
		return err;

	/* extract values out of the header */
	glort = FM10K_MSG_HDR_FIELD_GET(dglort_map, LPORT_MAP_GLORT);
	mask = FM10K_MSG_HDR_FIELD_GET(dglort_map, LPORT_MAP_MASK);

	/* verify mask is set and none of the masked bits in glort are set */
	if (!mask || (glort & ~mask))
		return FM10K_ERR_PARAM;

	/* verify the mask is contiguous, and that it is 1's followed by 0's */
	if (((~(mask - 1) & mask) + mask) & FM10K_DGLORTMAP_NONE)
		return FM10K_ERR_PARAM;

	/* record the glort, mask, and port count */
	hw->mac.dglort_map = dglort_map;

	return 0;
}