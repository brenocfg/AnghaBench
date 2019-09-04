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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  igb_get_pcs_speed_and_duplex_82575 (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_get_speed_and_duplex_copper (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 igb_get_link_up_info_82575(struct e1000_hw *hw, u16 *speed,
					u16 *duplex)
{
	s32 ret_val;

	if (hw->phy.media_type != e1000_media_type_copper)
		ret_val = igb_get_pcs_speed_and_duplex_82575(hw, speed,
							       duplex);
	else
		ret_val = igb_get_speed_and_duplex_copper(hw, speed,
								    duplex);

	return ret_val;
}