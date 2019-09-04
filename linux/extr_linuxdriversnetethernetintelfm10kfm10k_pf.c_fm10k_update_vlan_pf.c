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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int FM10K_VLAN_TABLE (scalar_t__,int) ; 
 int FM10K_VLAN_TABLE_VID_MAX ; 
 scalar_t__ FM10K_VLAN_TABLE_VSI_MAX ; 
 int fm10k_read_reg (struct fm10k_hw*,int) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int,int) ; 

__attribute__((used)) static s32 fm10k_update_vlan_pf(struct fm10k_hw *hw, u32 vid, u8 vsi, bool set)
{
	u32 vlan_table, reg, mask, bit, len;

	/* verify the VSI index is valid */
	if (vsi > FM10K_VLAN_TABLE_VSI_MAX)
		return FM10K_ERR_PARAM;

	/* VLAN multi-bit write:
	 * The multi-bit write has several parts to it.
	 *               24              16               8               0
	 *  7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * | RSVD0 |         Length        |C|RSVD0|        VLAN ID        |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 *
	 * VLAN ID: Vlan Starting value
	 * RSVD0: Reserved section, must be 0
	 * C: Flag field, 0 is set, 1 is clear (Used in VF VLAN message)
	 * Length: Number of times to repeat the bit being set
	 */
	len = vid >> 16;
	vid = (vid << 17) >> 17;

	/* verify the reserved 0 fields are 0 */
	if (len >= FM10K_VLAN_TABLE_VID_MAX || vid >= FM10K_VLAN_TABLE_VID_MAX)
		return FM10K_ERR_PARAM;

	/* Loop through the table updating all required VLANs */
	for (reg = FM10K_VLAN_TABLE(vsi, vid / 32), bit = vid % 32;
	     len < FM10K_VLAN_TABLE_VID_MAX;
	     len -= 32 - bit, reg++, bit = 0) {
		/* record the initial state of the register */
		vlan_table = fm10k_read_reg(hw, reg);

		/* truncate mask if we are at the start or end of the run */
		mask = (~(u32)0 >> ((len < 31) ? 31 - len : 0)) << bit;

		/* make necessary modifications to the register */
		mask &= set ? ~vlan_table : vlan_table;
		if (mask)
			fm10k_write_reg(hw, reg, vlan_table ^ mask);
	}

	return 0;
}